/* leetcode 977
双指针法 大的在两头 重塑一个数组，类似合并链表
*/

class 有序数组的平方 {
    public int[] sortedSquares(int[] nums) {
        int l = 0, r = nums.length - 1;
        int[] newArr = new int[nums.length];
        for (int i=nums.length-1; i>=0; --i) {
            if (nums[l]*nums[l] > nums[r]*nums[r]) {
                newArr[i] = nums[l]*nums[l];
                ++l;
            }
            else {
                newArr[i] = nums[r]*nums[r];
                --r;
            }
        }
        return newArr;
    }
}