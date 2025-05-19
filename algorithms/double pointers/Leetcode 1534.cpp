class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size();
        int result = 0;
        //int num_freq[1637]={0};

        //维护一个在坐标j之前统计arr值-次数的哈希表
        //由于我们只关心值的范围，因此横向压缩可以节省迭代次数
        //由于后面用了前缀和缓存，因此这里不需要使用num_freq数组
        int freq_presum[1637]={0};
        //由于需要重复查询区间和，因此用前缀和缓存
        //把查询i的复杂度需求降到了O（1）

        for (int j=1;j<n-1;j++){
            //freq[arr[j-1]]++;
            for(int i=arr[j-1]+1;i<1637;i++){
                freq_presum[i]++;
            }
            for(int k=j+1;k<n;k++){
                if(abs(arr[j]-arr[k])<=b){
                    int inf=max(arr[j]-a,arr[k]-c);
                    if(inf<0) inf=0;
                    int sup=min(arr[j]+a,arr[k]+c);
                    result+=(freq_presum[sup+1]-freq_presum[inf]);
                }
            }
        }
        
        return result;
    }
};