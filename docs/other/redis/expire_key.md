##### How redis expire keys

- a passive way
A key is passively expired simply when some client tries to access it, and the key is found to be timed out.

- an active way
Of course this is not enough as there are expired keys that will never be accessed again. These keys should be expired anyway, so periodically Redis tests a few keys at random among keys with an expire set. All the keys that are already expired are deleted from the keyspace
