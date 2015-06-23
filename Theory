Locks
=====

individual locks
----------------

Idea: 
	every collector has his own lock and locks are locked in ascending order.

Problem:
	Deadlock if one collector has all the money and his own lock, as nobody can
	get money from him.

Possible solution:
	After every attempted transaction the locks are freed and the collector
	remembers his target if no transaction could be made. Retry next time.

single lock
-----------

Idea:
	there is one single lock which is locked if someone wants to make a
	transaction and freed after the transaction.

Problem:
	Again we get a deadlock if one has all the money and the transaction lock.
	Also we get a deadlock if one wants to have money frome one who has none.

Possible solution:
	If there is no transaction possible, the lock is freed and the next
	transaction may start. The target has to bee saved in the collectors memory.
