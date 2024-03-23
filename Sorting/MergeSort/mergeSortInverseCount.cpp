#include <iostream>
#include <vector>

std::vector<int> MergeSortInversionCount(std::vector<int> vec, int& inversions)
{
    if(vec.size() < 2)
    {
        //base part
        return vec;
    }
    else
    {
        //recursive part
        std::vector<int> result;
        
        std::vector<int> left;
        left.insert(left.end(), vec.begin(), vec.begin() + (vec.size() / 2));
        std::vector<int> right;
        right.insert(right.end(), vec.begin() + (vec.size() / 2), vec.end());
        
        left = MergeSortInversionCount(left, inversions);
        right = MergeSortInversionCount(right, inversions);
        int i = 0;
        int j = 0;
        while((i < left.size()) && (j < right.size()))
        {
            if(left[i] < right[j])
            {
                result.push_back(left[i]);
                ++i;
            }
            else
            {
                //counting how many inversions between 
                //left(i to end) and right(j-th element)
                result.push_back(right[j]);
                inversions += (left.size() - i);
                ++j;
            }
        }
        if(i < left.size())
        {
            result.insert(result.end(), left.begin() + i, left.end());
        }
        else
        {
            result.insert(result.end(), right.begin() + j, right.end());
        }
        
        return result;
    }
}

int main()
{
    int inversions = 0;
    std::vector<int> test = {6, 5, 7, 4, 3};
    test = MergeSortInversionCount(test, inversions);
    for(int el : test)
    {
        std::cout<<el<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Number of inversions in vector is "<<inversions<<std::endl;

    return 0;
}
