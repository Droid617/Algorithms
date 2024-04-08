void InsertionSort(std::vector<int>& vec)
{
    for(int i = 1; i < vec.size(); ++i)
    {
        int elem = vec[i];
        int j = i - 1;
        if(vec[j] < elem)
        {
            continue;
        }
        while((j >= 0) && (vec[j] >= elem))
        {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = elem;
    }
}
