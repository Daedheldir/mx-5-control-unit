#pragma once

namespace dh
{
    class CharArrOperations
    {
    public:
        static bool Contains(char arr[], size_t arrSize, char searchedArr[], size_t searchedArrSize)
        {
            //Serial.print("Comparing ");
            //Serial.print(arr);
            //Serial.print(" with ");
            //Serial.println(searchedArr);
            for (int i = 0; i < arrSize - searchedArrSize; ++i)
            {
                int foundCount = 0;
                for (int j = 0; j < searchedArrSize; ++j)
                {
                    if (arr[i + j] == searchedArr[j])
                    {
                        foundCount++;
                    }
                }
                //if sequence was found
                if (foundCount == searchedArrSize)
                {
                    //Serial.println("Sequence found");
                    return true;
                }

                //if seq wasn't found then continue
            }

            //return false if seq wasn't found
            //Serial.println("Sequence not found");
            return false;
        };

        //returns index of sequence or -1 if sequence wasn't found
        static bool FindIndexOfSeq(char arr[], size_t arrSize, char searchedArr[], size_t searchedArrSize)
        {
            int seqIndex = -1;

            for (int i = 0; i < arrSize - searchedArrSize; ++i)
            {
                int foundCount = 0;
                for (int j = 0; j < searchedArrSize; ++j)
                {
                    if (arr[i + j] == searchedArr[j])
                    {
                        foundCount++;
                    }
                }
                //if sequence was found
                if (foundCount == searchedArrSize)
                {
                    return i;
                }

                //if seq wasn't found then continue
            }

            //return false if seq wasn't found
            return -1;
        };

    private:
        CharArrOperations(){};
    };
}