#pragma once

template <typename Number>
class RollingAverage
{
private:
  int capacity;
  Number *values; // Pointer to an array of Numbers
  int size;       // Current number of elements in the array

public:
  // Constructor that takes the capacity as an argument
  RollingAverage(unsigned int capacity) : capacity(capacity), size(0)
  {
    values = new Number[capacity]; // Allocate memory for the array
  }

  // Destructor to free allocated memory
  ~RollingAverage()
  {
    delete[] values;
  }

  Number getAverage()
  {
    if (size == 0)
    {
      // Handle empty array case (optional: return specific value or throw error)
      return 0; // Example: return 0 for empty average
    }

    Number sum = 0;
    for (int i = 0; i < size; i++)
    {
      sum += values[i];
    }
    return static_cast<Number>(sum) / static_cast<Number>(size);
  }

  void addValue(Number value)
  {
    if (size == capacity)
    {
      // Shift elements one position to the left if full
      for (int i = 1; i < capacity; i++)
      {
        values[i - 1] = values[i];
      }
    }
    else
    {
      size++;
    }
    values[size - 1] = value; // Add new value at the end
  }

  void resize(int newCapacity)
  {
    if (newCapacity <= 0)
    {
      // Handle invalid resize case (optional: throw error)
      return;
    }

    Number *temp = new Number[newCapacity];           // Allocate temporary array
    int elementsToCopy = std::min(size, newCapacity); // Copy min of current and new size
    for (int i = 0; i < elementsToCopy; i++)
    {
      temp[i] = values[i];
    }
    delete[] values; // Free old memory
    values = temp;   // Update pointer to new array
    capacity = newCapacity;
    size = elementsToCopy; // Update size based on copied elements
  }
};
