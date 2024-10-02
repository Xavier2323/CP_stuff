#define st clock_t qua = clock();
#define ed cout << "time: " << (double)(clock()-qua)/CLOCKS_PER_SEC << " sec\n";

unsigned int genseed() {
  auto now = chrono::system_clock::now();
  auto timestamp = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch());
  return static_cast<unsigned int>(timestamp.count());
}
 
int main() {
  unsigned int seed = genseed();
  mt19937 engine(seed);
  cout<<engine(); // random num
  return 0;
}