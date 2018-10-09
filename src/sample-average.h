// TODO: document this

template <int N>
class sample_average
{
  int  samples[N];
  long total;
  int  index;

public:
  sample_average(void) : index(0)
  {
    for (int i = 0; i < N; ++i) samples[i] = 0;
  }

  sample_average &operator<<(int const x)
  {
    total -= samples[index];
    total += (samples[index++] = x);
    index %= N;
    return *this;
  }

  inline int mean(void) const
  {
    return total / N;
  }
};
