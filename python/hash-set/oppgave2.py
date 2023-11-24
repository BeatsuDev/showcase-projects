from abc import abstractmethod

class HashSet:
    def __init__(self, capacity):
        self.capacity = capacity
        self.size = 0
        self.collisions = 0
        self.array = [None] * capacity

    def hash1(self, key):
        # return key % self.capacity
        # return ((key << 5) * 5381) % self.capacity
        hash_value = (5**0.5 - 1) / 2
        key = key & 0x7FFFFFFF

        return int((key * hash_value) % 1 * self.capacity)
    
    @abstractmethod
    def hash2(self, key):
        pass

    def insert(self, key):
        if self.size >= self.capacity:
            raise Exception("Set is full")

        index = self.hash1(key)
        step = self.hash2(key)

        while self.array[index] is not None:
            index = (index + step) % self.capacity
            self.collisions += 1

        self.array[index] = key
        self.size += 1

    def contains(self, key):
        index = self.hash1(key)
        step = self.hash2(key)

        while self.array[index] is not None:
            if self.array[index] == key:
                return True
            index = (index + step) % self.capacity

        return False

class LinearProbeHashSet(HashSet):
    # A Linear Probe Hash Set is just a double hash set with
    # step size (return value of second hash function) 1.
    def hash2(self, key):
        return 1

class DoubleHashSet(HashSet):
    def hash2(self, key):
        return ((key << 5) + 5381) % self.capacity
        # return 1 + (key % (self.capacity - 1))  # Faster for prime sizes, but doesn't work for powers of 2.


import random
import time

def generate_random_nums(size):
    nums = [0]
    for i in range(1, size):
        nums.append(nums[i-1] + random.randint(1, 1000))
    random.shuffle(nums)
    return nums

def time_function(hash_set, nums):
    size = len(nums)
    i = 0
    start = time.perf_counter()
    while i < size // 2:
        hash_set.insert(nums[i])
        i += 1

    collisions_50 = hash_set.collisions
    time_50 = time.perf_counter() - start
    while i < size * 0.8:
        hash_set.insert(nums[i])
        i += 1

    collisions_80 = hash_set.collisions
    time_80 = time.perf_counter() - start
    while i < size * 0.9:
        hash_set.insert(nums[i])
        i += 1

    collisions_90 = hash_set.collisions
    time_90 = time.perf_counter() - start
    while i < size * 0.99:
        hash_set.insert(nums[i])
        i += 1

    collisions_99 = hash_set.collisions
    time_99 = time.perf_counter() - start
    while i < size:
        hash_set.insert(nums[i])
        i += 1

    collisions_end = hash_set.collisions
    time_end = time.perf_counter() - start

    print("Time 50%: {}, Collisions: 50%: {}".format(time_50, collisions_50))
    print("Time 80%: {}, Collisions: 80%: {}".format(time_80, collisions_80))
    print("Time 90%: {}, Collisions: 90%: {}".format(time_90, collisions_90))
    print("Time 99%: {}, Collisions: 99%: {}".format(time_99, collisions_99))
    print("Time end: {}, Collisions: end: {}".format(time_end, collisions_end))

    times = [
        (50, time_50),
        (80, time_80),
        (90, time_90),
        (99, time_99),
        (100, time_end)
    ]

    collisions = [
        (50, collisions_50),
        (80, collisions_80),
        (90, collisions_90),
        (99, collisions_99),
        (100, collisions_end)
    ]

    return times, collisions


import matplotlib.pyplot as plt

if __name__ == "__main__":
    size = 2**17
    linear_hash_set = LinearProbeHashSet(size)
    double_hash_set = DoubleHashSet(size)

    nums = generate_random_nums(size)
    nums2 = [*nums]

    print("Timing and checking collisions for linear probe hash set")
    t0, c0 = time_function(linear_hash_set, nums)

    print("Timing and checking collisions for double hash set")
    t1, c1 = time_function(double_hash_set, nums2)

    fig, ax = plt.subplots(2)

    ax[0].plot(*zip(*t0), 'bD', label="Times linear probe")
    ax[0].plot(*zip(*t1), 'mo', label="Times double hash")

    ax[1].plot(*zip(*c0), 'c*', label="Collisions linear probe")
    ax[1].plot(*zip(*c1), 'r+', label="Collisions double hash")
    
    fig.legend()
    plt.show()

""" Rapport:
Tidskompleksiteten til linear probe vokser sakte helt fram til den blir 90% fullt.
Etter det vokser den eksponensielt større og øker som regel 3x-5x på den siste prosenten.
Antall kollisjoner vokser i takt med dette og det ser ut til å være en direkte korrelasjon 
mellom antall kollisjoner og tidsforbruk.

Tidskompleksiteten til double hash ser også ut til å vokse sakte fram til den blir 99% fullt.
Kollisjonstallet er mye lavere ved alle fyllingsgrader av hash-settene og selv på den siste
prosenten, øker tidsforbruket til double hash settet med omtrent 1.5-2x.

Resultatene virker likt på de andre hashfunksjonene som er kommentert ut.
"""