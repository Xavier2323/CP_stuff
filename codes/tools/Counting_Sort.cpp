vector<unsigned> counting_sort(const vector<unsigned> &Arr, unsigned K) {
	vector<unsigned> Bucket(k, 0);
	for(auto x: Arr) 
		++Bucket[x];
	partial_sum(Bucket.begin(), Bucket.end(), Bucket.begin());
	vector<unsigned> Ans(Arr.size());
	for(auto Iter = Arr.rbegin(); Iter != Arr.rend(); ++Iter) Ans[--Bucket[*Iter]] = *Iter;
	return Ans;
}
