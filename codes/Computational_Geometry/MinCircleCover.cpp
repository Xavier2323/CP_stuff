const double eps = 1e-10;
int sign(double a){
  return fabs(a)<eps?0:a>0?1:-1;
}
template<typename T>
T len(point<T> p){
  return sqrt(p.dot(p));
}
template<typename T>
point<T> findCircumcenter(point<T> A,point<T> B,point<T> C){
  point<T> AB = B-A;
  point<T> AC = C-A;
  T AB_len_sq = AB.x*AB.x+AB.y*AB.y;
  T AC_len_sq = AC.x*AC.x+AC.y*AC.y;
  T D = AB.x*AC.y-AB.y*AC.x;
  T X = A.x+(AC.y*AB_len_sq-AB.y*AC_len_sq)/(2*D);
  T Y = A.y+(AB.x*AC_len_sq-AC.x*AB_len_sq)/(2*D);
  return point<T>(X,Y);
}
template<typename T>
pair<T, point<T>> MinCircleCover(vector<point<T>> &p){   
// 回傳最小覆蓋圓{半徑,中心}
  random_shuffle(p.begin(),p.end());
  int n = p.size();
  point<T> c = p[0]; T r = 0;
  for(int i=1;i<n;i++){
    if(sign(len(c-p[i])-r) > 0){ // 不在圓內
      c = p[i], r = 0;
      for(int j=0;j<i;j++){
        if(sign(len(c-p[j])-r) > 0) {
          c = (p[i]+p[j])/2.0;
          r = len(c-p[i]);
          for(int k=0;k<j;k++) {
            if(sign(len(c-p[k])-r) > 0){
    //c=triangle<T>(p[i],p[j],p[k]).circumcenter();
              c = findCircumcenter(p[i],p[j],p[k]);
              r = len(c-p[i]);
            }
          }
        }
      }
    }
  }
  return make_pair(r,c);
}