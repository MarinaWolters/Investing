###############################################################
# File: A simple script that calculates how long does it take #
#       for a machine to solve 2^32 hashes as it was intial   #
#       difficulty=1 to mine one block on Bitcoin network.    #
###############################################################

import timeit

t = timeit.Timer('hashlib.sha256(nonce)', setup='import hashlib; import os; nonce = os.urandom(64)')
n = 2**20
hash_time = t.timeit(number=n)
total_time = (hash_time*2**32/n)/60
print( f"{total_time} minutes to compute 2^32 hashes" )

# 30.63611166725556 minutes to compute 2^32 hashes
# On my MacBook Pro with M1 Apple Silicon

