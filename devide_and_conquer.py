import numpy as np

from typing import List
from typing import Union
from typing import Callable
from typing import Optional

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



