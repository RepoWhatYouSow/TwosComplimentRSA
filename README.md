# TwosComplimentRSA
Standard RSA with a buffer using twos compliment. Since the N value (product of two primes) needs to be at least as big as the largest ascii value, the corresponding D value when used for decrption surpasses 64 bits. This means that a bigNum library must be used for proper use of this program. Individual components work when tested.


TODO:
-Convert to GMP library
