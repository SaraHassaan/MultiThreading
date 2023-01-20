using System;
using System.Diagnostics;
using System.Linq;
using System.Collections.Generic;
using System.Threading;

namespace CSharpExcersices
{
    struct ArrayInfo
    {
        public int[] arr;
        public int size;
    }
    class MergeSort
    {
        public void Sort(int[]arr, int size)
        {
            ArrayInfo arrayInfo = new ArrayInfo();
            arrayInfo.arr = arr;
            arrayInfo.size = size;
            Object TargetInfo = arrayInfo;
            Stopwatch timer = new Stopwatch();
            timer.Start();

            SortArray(TargetInfo);
            timer.Stop();
            
            foreach (int num in arr)
            {
                Console.WriteLine(num);
            }
            Console.WriteLine("Elapsed={0}", timer.Elapsed);

        }
        private void SortArray(Object target)
        {
            ArrayInfo arrayInfo = (ArrayInfo)target;
            int len = arrayInfo.size;
            if (1 == len) return;

            int mid = len / 2;
            ArrayInfo arrayLeft;
            ArrayInfo arrayRight;
            arrayLeft.arr = new int[mid];
            arrayLeft.size = mid;

            arrayRight.size = len - mid;
            arrayRight.arr = new int[arrayRight.size];

            for(int i = 0; i < mid; ++i)
            {
                arrayLeft.arr[i] = arrayInfo.arr[i];
            }

            for(int i = mid; i < len; ++i)
            {
                arrayRight.arr[i-mid] = arrayInfo.arr[i];
            }

            Object targetLeft = arrayLeft;
            object targetRight = arrayRight;


            ParameterizedThreadStart parameterizedThreadStart = new ParameterizedThreadStart(SortArray);
            Thread t = new Thread(SortArray);

            t.Start(targetLeft);
            SortArray(targetRight);
           
            t.Join();

            Merge(arrayInfo.arr, arrayLeft.arr, arrayRight.arr, arrayLeft.size, arrayRight.size);


        }
        private void Merge(int[] arr, int[] left, int[]right, int nL, int nR)
        {
            int i = 0, j = 0, k = 0;

            while(i < nL && j < nR)
            {
                if(left[i] < right[j])
                {
                    arr[k] = left[i++];
                }
                else
                {
                    arr[k] = right[j++];
                }
                ++k;
            }

            while( i < nL)
            {
                arr[k++] = left[i++];
            }
            while(j < nR)
            {
                arr[k++] = right[j++];
            }
        }
    }
}