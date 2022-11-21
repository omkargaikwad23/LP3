from collections import *
from heapq import *

text="aaabbccccd"

d=defaultdict(int)
for i in text:
    d[i]+=1

pq=[]
for i in d.items():
    ch,freq=i
    pq.append([freq,[ch,""]])

heapify(pq)

while(len(pq)>1):
    left=heappop(pq)
    right=heappop(pq)

    for pair in left[1:]:
        pair[1]="0"+pair[1]
    for pair in right[1:]:
        pair[1]="1"+pair[1]

    l=[left[0]+right[0]]
    l+=right[1:]+left[1:]

    heappush(pq, l)

huff_list=right[1:]+left[1:]
print("Huffman_list=",huff_list)

'''
Huffman_list= [['H', '111'], ['E', '110'], ['O', '10'], ['L', '0']]
'''