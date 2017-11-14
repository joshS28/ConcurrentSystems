#define NUM_PHIL 4

bool pthinking[NUM_PHIL],  phungry[NUM_PHIL],  peating[NUM_PHIL] = false;
int forks[NUM_PHIL] = -1;

proctype p(int i) {
	int right = i; int left = (i + 1) % NUM_PHIL;
Think:	atomic { peating[i] = false; phungry[i] = true; };
	/* NOTHING */

Hungry: atomic { pthinking[i] = false; phungry[i] = true; };
	if :: skip ;
		atomic { forks[left] == -1 -> forks[left] = i };
		atomic { forks[right] == -1 -> forks[right] = i };
	   :: skip ;
		atomic { forks[right] == -1 -> forks[right] = i }; 
		atomic { forks[left] == -1 -> forks[left] = i };
	fi;
Eating: atomic { phungry[i] = false; peating[i] = true; };
Done:	forks[right] = -1; forks[left] = -1;
	goto Think;
}

init {
	run p(0);
	run p(1);
	run p(2);
	run p(3);
}

/*never  {    
T0_init:
	do
	:: (! ((peating)) && (phungry)) -> goto accept_S4
	:: (1) -> goto T0_init
	od;
accept_S4:
	do
	:: (! ((peating))) -> goto accept_S4