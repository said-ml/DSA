import numpy as np

from typing import List
from typing import Union
from typing import Callable
from typing import Optional

def merge(nums1, nums2):
    # List to restore results
    merged=[]
    i, j=0,0
    # loops over the two lists
    while i<len(nums1) and j<len(nums2):

          if nums1[i]<nums2[j]:
              merged.append(nums1[i])
              # increment i
              i+=1

          else :
              merged.append(nums2[j])
              # increment i
              j+=1

    # Getting the remai ing parts
    nums1_tails=nums1[i:]
    nums2_tails = nums2[j:]

    return merged+nums1_tails+nums2_tails


def  merge_sort(nums:Optional[List[int]])->Optional[List[int]]:

     if len(nums)==0:
         raise ValueError(f'the {nums} is empty')

     elif len(nums)==1:
         return nums

     else:
         # get the midpoint
         mid=len(nums)//2

         # split the list into halves
         left=nums[:mid]
         right=nums[mid:]

         # resolve the prblem for each half recursively
         left_sorted, right_sorted=merge_sort(left), merge_sort(right)

         # combine the half solution
         sorted_nums=merge(left_sorted, right_sorted)

         return sorted_nums



