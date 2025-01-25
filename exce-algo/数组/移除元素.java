/* leetcode 27
快慢双指针法
感觉c++和java各有各的唐
*/

class 移除元素 {
    public int removeElement(int[] nums, int val) {
        int l = 0, r = 0;
        for (; r < nums.length; ++r)
        {
            if (val != nums[r]) {
                nums[l++] = nums[r];
            }
        }
        return l;
    }
}