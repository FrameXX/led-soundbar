#pragma once

template <typename Number, int size>
class RollingArray
{
private:
  constexpr static int arraySize = size;
  Number values[size];
  int cursorIndex = 0;

public:
  RollingArray(Number defaultFill = 0)
  {
    memset(values, defaultFill, sizeof(values));
  }

  void fill(Number value)
  {
    memset(values, value, sizeof(values));
  }

  void addValue(Number value)
  {
    values[cursorIndex] = value;
    cursorIndex = (cursorIndex + 1) % arraySize;
  }

  Number getSum() const
  {
    Number sum = 0;
    for (int i = 0; i < arraySize; i++)
    {
      sum += values[i];
    }
    return sum;
  }

  Number getAverage() const
  {
    return static_cast<Number>(getSum() / arraySize);
  }
};