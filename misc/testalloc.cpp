// TestInterop.cpp : Implementation of CTestInterop

#include "stdafx.h"
#include "TestInterop.h"
#include <map>
#include <vector>

// CTestInterop

// <MyCustomAlloc>

long g_nCnt = 0;  // total # blocks allocated
long g_nTot = 0;  // total allocated

template<class T>
class MyCustomAlloc
/*
 * A custom allocator: given a pool of memory to start, just dole out consecutive memory blocks.
 * this could be faster than a general purpose allocator.
 * E.G. it could take advantage of constant sized requests (as in a RedBlack tree)
 */
{
private:
    void operator=(const MyCustomAlloc &);

public:
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;

    byte *m_pool;
    unsigned m_nPoolSize;

    MyCustomAlloc(byte *pool, int nPoolSize) {
        Init();
        m_pool = pool;
        m_nPoolSize = nPoolSize;
    }

    MyCustomAlloc(int n) {
        Init();
    }

    MyCustomAlloc() {
        Init();
    }

    void Init() {
        m_pool = 0;
        m_nPoolSize = 0;
        g_nCnt = 0;
        g_nTot = 0;
    }

    MyCustomAlloc(const MyCustomAlloc &obj) { // copy constructor
        Init();
        m_pool = obj.m_pool;
        m_nPoolSize = obj.m_nPoolSize;
    }

    template<class _Other>
    MyCustomAlloc(const MyCustomAlloc<_Other> &other) {
        Init();
        m_pool = other.m_pool;
        m_nPoolSize = other.m_nPoolSize;
    }

    ~MyCustomAlloc() { }

    template<class U>
    struct rebind {
        typedef MyCustomAlloc<U> other;
    };

    pointer address(reference r) const {
        return &r;
    }

    const_pointer address(const_reference r) const {
        return &r;
    }

    pointer allocate(size_type n, const void * /*hint*/= 0) {
        pointer p;
        unsigned nSize = n * sizeof(T);
        if (m_pool) { // if we have a mem pool from which to allocated
            p = (pointer) m_pool;// just return the next available mem in the pool
            if (g_nTot + nSize > m_nPoolSize) {
                _ASSERT(0);//,"out of mem pool");
                return 0;
            }
            m_pool += nSize;  // and bump the pointer
        } else {
            p = (pointer) malloc(nSize);// no pool: just use malloc
        }
        g_nCnt += 1;
        g_nTot += nSize;
        _ASSERTE(p);
        return p;
    }

    void deallocate(pointer p, size_type /*n*/) {
        if (!m_pool) {// if there's a pool, nothing to do
            free(p);
        }
    }

    void construct(pointer p, const T &val) {
        new(p) T(val);
    }

    void destroy(pointer p) {
        p->~T();
    }

    size_type max_size() const {
        return ULONG_MAX / sizeof(T);
    }
};

template<class T>
bool operator==(const MyCustomAlloc<T> &left, const MyCustomAlloc<T> &right) {
    if (left.m_pool == right.m_pool) {
        return true;
    }
    return false;
}

template<class T>
bool operator!=(const MyCustomAlloc<T> &left, const MyCustomAlloc<T> &right) {
    if (left.m_pool != right.m_pool) {
        return true;
    }
    return false;
}

// </MyCustomAlloc>

using namespace std;

typedef pair<CComBSTR, int> PairStringInt;

// DoTest is a template func that does the test.

// it's a template because 2 diff map types are passed in





#define NSIZE 2


template<typename TMap>

void DoTest(TMap oMap, CComBSTR bstrType) {

    for (int nItem = 0; nItem < NSIZE; nItem++) // 2nd time through adds dupes, no prob: ignored

    {

        // as you single step through here, observe the value of

        // oMap in the Locals window!

        oMap.insert(PairStringInt(CComBSTR("Jan"), 31));

        oMap.insert(PairStringInt(CComBSTR("Feb"), 28));

        oMap.insert(PairStringInt(CComBSTR("Mar"), 31));

        oMap.insert(PairStringInt(CComBSTR("Apr"), 30));

        oMap.insert(PairStringInt(CComBSTR("May"), 31));

        oMap.insert(PairStringInt(CComBSTR("Jun"), 30));

        oMap.insert(PairStringInt(CComBSTR("Jul"), 31));

        if (nItem == 0) {

            // declare an iterator

            TMap::const_iterator it;

            // now iterate through the collection

            for (it = oMap.begin(); it != oMap.end(); it++) { // note they're sorted!

                wchar_t buf[1000];

                CComBSTR strOutput(bstrType);

                strOutput.Append(L" ");

                strOutput.Append(it->first);

                strOutput.Append(L" ");

                _itow_s(it->second, buf, 10, 10);

                strOutput.Append(buf); // hi Crescens2k

                strOutput.Append(L"\n");

                OutputDebugString(strOutput);

            }

        }

    }

    oMap.clear();

}


#define NITERATIONS 1000

#define NumItemsToAdd 10000

#define POOLSIZE (1040208+100)


struct SomeBigData {

    long id;

    long dummy[20];

} b1 = {1, {1, 1}},

        b2 = {2, {2, 2}};


typedef pair<long, SomeBigData> mapData; // a pair that holds some data



template<typename TMap>

void DoTestTiming(TMap oMap) {

    // now insert a few big items

    for (int nItem = 0; nItem < NumItemsToAdd; nItem++) // # items to add to the maps

    {

        b1.id = nItem;

        b2.id = nItem;

        oMap.insert(mapData(nItem, b1));

    }

}


void TestTiming(int nIter) {

    char buff[1000];

    byte *pool = 0;

    for (int iType = 0; iType < 3; iType++) // the map types

    {

        int nTotTime = 0;


        DWORD nTickStart = GetTickCount();

        for (int nIter = 0; nIter < NITERATIONS; nIter++) {

            g_nTot = 0;

            g_nCnt = 0;

            switch (iType) {

                case 0: {

                    map<long, SomeBigData> oMap0;

//                            OutputDebugString(L"Using plain map ");

//                            same as   multimap<long, SomeBigData, less<long>, std::allocator<std::pair<long, SomeBigData> > > oMap0;

                    DoTestTiming(oMap0);

                }

                    break;

                case 1: {

                    typedef MyCustomAlloc<pair<long, SomeBigData> > MyAllocator;


                    map<long, SomeBigData, less<long>, MyAllocator> oMap1;

//                            OutputDebugString(L"custom alloc ");

                    DoTestTiming(oMap1);

                }

                    break;

                case 2:

                    if (pool == 0) {

                        pool = (byte *) malloc(POOLSIZE);

                    }

                    {

                        typedef MyCustomAlloc<pair<long, SomeBigData> > MyAllocator;

                        MyAllocator z = MyAllocator(pool, POOLSIZE);

//                            OutputDebugString(L"Custom pool ");

                        map<long, SomeBigData, less<long>, MyAllocator> oMap2(less<long>(), z);

                        DoTestTiming(oMap2);

                    }

                    break;

            }

            free(pool); // ok to free null (fast too)

            pool = 0;



//                _snprintf_s(buff,sizeof(buff),"Done nType = %d nLoop = %d mSecs = %7d  %d  %d\n", iType, nIter, nTickEnd, g_nTot, g_nCnt);

//                OutputDebugStringA(buff);

        }

        DWORD nTickEnd = GetTickCount() - nTickStart;

        nTotTime += nTickEnd;


        _snprintf_s(buff, sizeof(buff), "  %d", nTotTime);

        OutputDebugStringA(buff);

    }

    OutputDebugString(L"\n");

}


STDMETHODIMP CTestInterop::Test(BSTR str, long *pRetval) {

    // single step through and observe the Locals window

    //some of this verbosity can be reduced via more typedefs

    // first we create a map object



    map<CComBSTR, int> MonthDict;


    DoTest(MonthDict, L"Using a map");


    multimap<CComBSTR, int> MultiMapMonthDict;


    DoTest(MultiMapMonthDict, "Using a multimap");



    // now we declare our own custom allocator, so the map will use it

    // this allocator just uses malloc/free (we don't give it a mem pool to use)

    typedef MyCustomAlloc<pair<CComBSTR, int> > MyAllocator;



    // we declare an instance of map which uses our custom allocator

    map<CComBSTR, int, less<CComBSTR>, MyAllocator> MonthDictCustomAlloc;


    DoTest(MonthDictCustomAlloc, L"Custom Alloc");



    // now we create a memory pool for our allocator to use

    byte *MyMemoryPool = (byte *) malloc(POOLSIZE);

    // open a debug window (Debug->Windows->Memory->1)

    // and drag the value of MyMemoryPool from the Locals window to it

    // single step through so you can see the memory being used for

    // the RedBlack tree.



    {// scoping so destructors fire before we free memory

        // we create an instance of the allocator

        MyAllocator z = MyAllocator(MyMemoryPool, POOLSIZE);



        // we declare an instance of map which uses our custom allocator using our mem pool

        map<CComBSTR, int, less<CComBSTR>, MyAllocator> MonthDictCustomMemoryPool(less<CComBSTR>(), z);

        DoTest(MonthDictCustomMemoryPool, L"Map with mempool");

    }

    free(MyMemoryPool); // ok to free(0)



    for (int i = 0; i < 40; i++) {

        TestTiming(i);

    }


    return S_OK;

}