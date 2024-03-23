#include <iostream>
#include <vector>

std::vector<int> MergeSort(std::vector<int> vec)
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
        
        left = MergeSort(left);
        right = MergeSort(right);

        //merging
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
                result.push_back(right[j]);
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
    std::vector<int> test = {6, 5, 3, 4, 1, 2, 7};
    test = MergeSort(test);
    for(int el : test)
    {
        std::cout<<el<<" ";
    }
    std::cout<<std::endl;

    return 0;
}
