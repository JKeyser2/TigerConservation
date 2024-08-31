// UMBC - CMSC 341 - Fall 2022 - Proj1
//#include "streak.h"
#include "streak.cpp"

#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Tester{
    public:
    

    /******************************************
    * Test function declarations go here! *
    ******************************************/
    // Inserting one node to the left and one node to the right of the root
    bool insertNormalCase(Streak &myStreak);
    // Inserting at the root
    bool insertEdgeCase(Streak &myStreak);
    // Inserting a negative number
    bool insertErrorCaseOne(Streak &myStreak);
    // Inserting an ID that already exists
    bool insertErrorCaseTwo(Streak &myStreak);

    bool insertLeftLeftRebalance(Streak &myStreak);
    bool insertLeftRightRebalance(Streak &myStreak);
    bool insertRightRightRebalance(Streak &myStreak);
    bool insertRightLeftRebalance(Streak &myStreak);

    bool removeNormalCase(Streak &myStreak);
    // Removing from root
    bool removeEdgeCase(Streak &myStreak);
    // The node does not exist
    bool removeErrorCase(Streak &myStreak);

    // The node being removed has a left child
    bool removeHasLeftChild(Streak &myStreak);
    // The node being removed has a right child
    bool removeHasRightChild(Streak &myStreak);
    // The node being removed has no children
    bool removeHasNoChildren(Streak& myStreak);
    // The node being removed has 2 children
    bool removeHasTwoChildren(Streak &myStreak);
    // The node being removed is the root and has a left child
    bool rootRemoveHasLeftChild(Streak &myStreak);
    // The node being removed is the root and has a right child
    bool rootRemoveHasRightChild(Streak &myStreak);
    // The node being removed is the root and has no children
    bool rootRemoveHasNoChildren(Streak& myStreak);
    // The node being removed is the root and has 2 children
    bool rootRemoveHasTwoChildren(Streak &myStreak);

    bool removeLeftLeftRebalance(Streak &myStreak);
    bool removeLeftRightRebalance(Streak &myStreak);
    bool removeRightRightRebalance(Streak &myStreak);
    bool removeRightLeftRebalance(Streak &myStreak);

    bool countTigerCubs(Streak &myStreak);
    bool removeDead(Streak &myStreak);

    bool insertionRunsOLogN();
    bool removeRunsOLogN();
};

int main () {
    
    Tester tester;

    {
        Streak myStreak;
        cout << "\nTesting the normal case of the insert function:\n\n";
        if (tester.insertNormalCase(myStreak) == true)
            cout << "\tNormal case of insert function passed!\n";
        else
            cout << "\tNormal case of insert function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the edge case of the insert function:\n\n";
        if (tester.insertEdgeCase(myStreak) == true)
            cout << "\tEdge case of insert function passed!\n";
        else
            cout << "\tEdge case of insert function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the first error case of the insert function:\n\n";
        if (tester.insertErrorCaseOne(myStreak) == true)
            cout << "\tError case one of insert function passed!\n";
        else
            cout << "\tError case one of insert function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the second error case of the insert function:\n\n";
        if (tester.insertErrorCaseTwo(myStreak) == true)
            cout << "\tError case two of insert function passed!\n";
        else
            cout << "\tError case two of insert function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the left-left rebalance after the insert function:\n\n";
        if (tester.insertLeftLeftRebalance(myStreak) == true)
            cout << "\tLeft-left rebalance after the insert function passed!\n";
        else
            cout << "\tLeft-left rebalance after the insert function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the left-right rebalance after the insert function:\n\n";
        if (tester.insertLeftRightRebalance(myStreak) == true)
            cout << "\tLeft-right rebalance after the insert function passed!\n";
        else
            cout << "\tLeft-right rebalance after the insert function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the right-right rebalance after the insert function:\n\n";
        if (tester.insertRightRightRebalance(myStreak) == true)
            cout << "\tRight-right rebalance after the insert function passed!\n";
        else
            cout << "\tRight-right rebalance after the insert function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the right-left rebalance after the insert function:\n\n";
        if (tester.insertRightLeftRebalance(myStreak) == true)
            cout << "\tRight-left rebalance after the insert function passed!\n";
        else
            cout << "\tRight-left rebalance after the insert function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node removed has a left child:\n\n";
        if (tester.removeHasLeftChild(myStreak) == true)
            cout << "\tRemove when the node has a left child passed!\n";
        else
            cout << "\tRemove when the node has a left child failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node removed has a right child:\n\n";
        if (tester.removeHasRightChild(myStreak) == true)
            cout << "\tRemove when the node has a right child passed!\n";
        else
            cout << "\tRemove when the node has a right child failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node removed has no children:\n\n";
        if (tester.removeHasNoChildren(myStreak) == true)
            cout << "\tRemove when the node has no children passed!\n";
        else
            cout << "\tRemove when the node has no children failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node removed has 2 children:\n\n";
        if (tester.removeHasTwoChildren(myStreak) == true)
            cout << "\tRemove when the node has two children passed!\n";
        else
            cout << "\tRemove when the node has two children failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node removed is at the root and has a left child:\n\n";
        if (tester.rootRemoveHasLeftChild(myStreak) == true)
            cout << "\tRemove from the root when the node has a left child passed!\n";
        else
            cout << "\tRemove from the root when the node has a left child failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node removed is at the root and has a right child:\n\n";
        if (tester.rootRemoveHasRightChild(myStreak) == true)
            cout << "\tRemove from the root when the node has a right child passed!\n";
        else
            cout << "\tRemove from the root when the node has a left child failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node removed is at the root and has no children:\n\n";
        if (tester.rootRemoveHasNoChildren(myStreak) == true)
            cout << "\tRemove from the root when the node has no children passed!\n";
        else
            cout << "\tRemove from the root when the node has no children failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node removed is at the root and has 2 children:\n\n";
        if (tester.rootRemoveHasTwoChildren(myStreak) == true)
            cout << "\tRemove from the root when the node has 2 children passed!\n";
        else
            cout << "\tRemove from the root when the node has 2 children failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting rebalancing when a node is removed. Left-left case:\n\n";
        if (tester.removeLeftLeftRebalance(myStreak) == true)
            cout << "\tLeft-left case of rebalancing after removal passed!\n";
        else
            cout << "\tLeft-left case of rebalancing after removal failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting rebalancing when a node is removed. Left-right case:\n\n";
        if (tester.removeLeftRightRebalance(myStreak) == true)
            cout << "\tLeft-right case of rebalancing after removal passed!\n";
        else
            cout << "\tLeft-right case of rebalancing after removal failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting rebalancing when a node is removed. Right-right case:\n\n";
        if (tester.removeRightRightRebalance(myStreak) == true)
            cout << "\tRight-right case of rebalancing after removal passed!\n";
        else
            cout << "\tLeft-right case of rebalancing after removal failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting rebalancing when a node is removed. Right-left case:\n\n";
        if (tester.removeRightLeftRebalance(myStreak) == true)
            cout << "\tRight-left case of rebalancing after removal passed!\n";
        else
            cout << "\tRight-left case of rebalancing after removal failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function normal case:\n\n";
        if (tester.removeNormalCase(myStreak) == true)
            cout << "\tRemove function normal case passed!\n";
        else
            cout << "\tRemove function normal case failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the node to be removed is the root\n\n";
        if (tester.removeEdgeCase(myStreak) == true)
            cout << "\tRemove function at the root passed!\n";
        else
            cout << "\tRemove function at the root failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove function when the ID does not exist:\n\n";
        if (tester.removeErrorCase(myStreak) == true)
            cout << "\tRemove function when ID does not exist passed!\n";
        else
            cout << "\tRemove function when ID does not exist failed!\n";
    }
 
    {
        Streak myStreak;
        cout << "\nTesting the count tiger cubs fuction:\n\n";
        if (tester.countTigerCubs(myStreak) == true)
            cout << "\tCounting tiger cubs function passed!\n";
        else
            cout << "\tCounting tiger cubs function failed!\n";
    }

    {
        Streak myStreak;
        cout << "\nTesting the remove dead function:\n\n";
        if (tester.removeDead(myStreak) == true)
            cout << "\tRemove dead function passed!\n";
        else
            cout << "\tRemove dead function failed!\n";
    }

/*
    {
        cout << "\nTesting that remove operator runs in O(logn):\n\n";
        if (tester.removeRunsOLogN() == true)
            cout << "\tRemove operator runs in O(logn) passed!\n";
        else
            cout << "\tRemove operator runs in O(logn) failed!\n";
    }
*/

/*
    {
        cout << "\nTesting that insertion operator runs in O(logn):\n\n";
        if (tester.insertionRunsOLogN() == true)
            cout << "\tInsertion operator runs in O(logn) passed!\n";
        else
            cout << "\tInsertion operator runs in O(logn) failed!\n";
    }
*/
    return 0;
}

bool Tester::insertNormalCase(Streak &myStreak){
    // Creats tiger object
    Tiger * newTiger = new Tiger(10, CUB, MALE, DEAD);

    // Stores in the root
    myStreak.m_root = newTiger;

    // Cretes second tiger object
    Tiger newTiger2 = Tiger(15, CUB, MALE, DEAD);

    // Should insert right of the root
    myStreak.insert(newTiger2);

    // Cretes third tiger object
    Tiger newTiger3 = Tiger(5, CUB, MALE, DEAD);

    // Should insert left of the root
    myStreak.insert(newTiger3);

    // Left of the root should be 5
    if(myStreak.m_root->m_left->getID() != 5){
        return false;
    }

    // Right of the root should be 15
    if(myStreak.m_root->m_right->getID() != 15){
        return false;
    }

    // Both 5 and 15 are in the correct places
    return true;
}

bool Tester::insertEdgeCase(Streak &myStreak){
   
    // Cretes tiger object
    Tiger newTiger2 = Tiger(15, CUB, MALE, DEAD);

    // Should insert at the root
    myStreak.insert(newTiger2);

    // Root should be 15
    if(myStreak.m_root->getID() != 15){
        return false;
    }

    // 15 is at the root
    return true;
}

bool Tester::insertErrorCaseOne(Streak &myStreak){
   
    // Cretes tiger object
    Tiger newTiger2 = Tiger(-15, CUB, MALE, DEAD);

    // Should not insert at the root as the ID is negative
    myStreak.insert(newTiger2);

    // Root should be nullptr
    if(myStreak.m_root != nullptr){
        return false;
    }

    // The root is nullptr
    return true;
}

bool Tester::insertErrorCaseTwo(Streak &myStreak){
   
    // Cretes tiger object
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);

    // Should insert 15 at the root
    myStreak.insert(newTiger);

    // Should not insert as 15 already exists
    myStreak.insert(newTiger);

    // Both left and right should be nullptr as 15 did not insert twice
    if(myStreak.m_root->m_left != nullptr || myStreak.m_root->m_right != nullptr){
        return false;
    }

    // There is only one node in the tree
    return true;
}

bool Tester::insertLeftLeftRebalance(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(5, CUB, MALE, DEAD);

    // Root
    myStreak.insert(newTiger);
    // Left
    myStreak.insert(newTiger2);
    // Left, Left
    myStreak.insert(newTiger3);

    // 10 should be the root
    if(myStreak.m_root->getID() != 10){
        return false;
    }
    // 5 should be the left node
    if(myStreak.m_root->getLeft()->getID() != 5){
        return false;
    }

    // 15 should be the right node
    if(myStreak.m_root->getRight()->getID() != 15){
        return false;
    }

    // All the nodes are where they are supposed to be
    return true;
}

bool Tester::insertLeftRightRebalance(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(12, CUB, MALE, DEAD);

    // Root
    myStreak.insert(newTiger);
    // Left
    myStreak.insert(newTiger2);
    // Left, Right
    myStreak.insert(newTiger3);

    // 12 should be the root
    if(myStreak.m_root->getID() != 12){
        return false;
    }
    // 10 should be the left node
    if(myStreak.m_root->getLeft()->getID() != 10){
        return false;
    }

    // 15 should be the right node
    if(myStreak.m_root->getRight()->getID() != 15){
        return false;
    }

    // All the nodes are where they are supposed to be
    return true;
}

bool Tester::insertRightRightRebalance(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(20, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(25, CUB, MALE, DEAD);

    // Root
    myStreak.insert(newTiger);
    // Right
    myStreak.insert(newTiger2);
    // Right
    myStreak.insert(newTiger3);

    // 20 should be the root
    if(myStreak.m_root->getID() != 20){
        return false;
    }
    // 15 should be the left node
    if(myStreak.m_root->getLeft()->getID() != 15){
        return false;
    }

    // 25 should be the right node
    if(myStreak.m_root->getRight()->getID() != 25){
        return false;
    }

    // All the nodes are where they are supposed to be
    return true;
}

bool Tester::insertRightLeftRebalance(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(20, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(17, CUB, MALE, DEAD);

    // Root
    myStreak.insert(newTiger);
    // Right
    myStreak.insert(newTiger2);
    // Right, Left
    myStreak.insert(newTiger3);

    // 17 should be the root
    if(myStreak.m_root->getID() != 17){
        return false;
    }
    // 15 should be the left node
    if(myStreak.m_root->getLeft()->getID() != 15){
        return false;
    }

    // 20 should be the right node
    if(myStreak.m_root->getRight()->getID() != 20){
        return false;
    }

    // All the nodes are where they are supposed to be
    return true;
}

bool Tester::removeHasLeftChild(Streak &myStreak){
    Tiger newTiger = Tiger(100, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(105, CUB, MALE, DEAD);
    Tiger newTiger4 = Tiger(8, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);

    // Remove 10
    myStreak.remove(10);

    // The new left child to the root should be 8
    if(myStreak.m_root->getLeft()->getID() != 8){
        return false;
    }

    return true;
}
  
bool Tester::removeHasRightChild(Streak &myStreak){
    Tiger newTiger = Tiger(100, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(105, CUB, MALE, DEAD);
    Tiger newTiger4 = Tiger(15, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);

    // Remove 10
    myStreak.remove(10);

    // The new left child to the root should be 15
    if(myStreak.m_root->getLeft()->getID() != 15){
        return false;
    }

    return true;
}

 
bool Tester::removeHasNoChildren(Streak& myStreak){
    Tiger newTiger = Tiger(100, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(105, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);

    // Remove 10
    myStreak.remove(10);

    // The new left child to the root should be nullptr
    if(myStreak.m_root->getLeft() != nullptr){
        return false;
    }

    return true;
}
 
bool Tester::removeHasTwoChildren(Streak &myStreak){
    Tiger newTiger = Tiger(100, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(105, CUB, MALE, DEAD);
    Tiger newTiger4 = Tiger(8, CUB, MALE, DEAD);
    Tiger newTiger5 = Tiger(11, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);
    myStreak.insert(newTiger5);

    // Remove 10
    myStreak.remove(10);

    // The new left child to the root should be 11
    if(myStreak.m_root->getLeft()->getID() != 11){
        return false;
    }

    // The left child to the left child of the root should be 8
    if(myStreak.m_root->getLeft()->getLeft()->getID() != 8){
        return false;
    }

    return true;
}

bool Tester::rootRemoveHasLeftChild(Streak &myStreak){
    Tiger newTiger = Tiger(100, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);

    // Remove 100
    myStreak.remove(100);

    // The new root should be 10
    if(myStreak.m_root->getID() != 10){
        return false;
    }

    return true;
}

bool Tester::rootRemoveHasRightChild(Streak &myStreak){
    Tiger newTiger = Tiger(100, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(105, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);

    // Remove 100
    myStreak.remove(100);

    // The new root should be 105
    if(myStreak.m_root->getID() != 105){
        return false;
    }

    return true;
}

bool Tester::rootRemoveHasNoChildren(Streak& myStreak){
    Tiger newTiger = Tiger(100, CUB, MALE, DEAD);

    myStreak.insert(newTiger);

    // Remove 100
    myStreak.remove(100);

    // The new root should be nullptr
    if(myStreak.m_root != nullptr){
        return false;
    }

    return true;
}

bool Tester::rootRemoveHasTwoChildren(Streak &myStreak){
    Tiger newTiger = Tiger(100, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(110, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(90, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);

    myStreak.remove(100);

    // New root should be 110
    if(myStreak.m_root->getID() != 110){
        return false;
    }

    // Left of the root should still be 90
    if(myStreak.m_root->m_left->getID() != 90){
        return false;
    }

    return true;
}

bool Tester::removeRightRightRebalance(Streak &myStreak){
    Tiger newTiger = Tiger(50, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(60, CUB, MALE, DEAD);
    Tiger newTiger4 = Tiger(70, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);

    myStreak.remove(10);

    // Root should now be 60
    if(myStreak.m_root->getID() != 60){
        return false;
    }

    // Left of the root should be 50
    if(myStreak.m_root->m_left->getID() != 50){
        return false;
    }

    // Right of the root should be 70
    if(myStreak.m_root->m_right->getID() != 70){
        return false;
    }

    return true;
}

bool Tester::removeRightLeftRebalance(Streak &myStreak){
    Tiger newTiger = Tiger(59, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(69, CUB, MALE, DEAD);
    Tiger newTiger4 = Tiger(65, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);

    myStreak.remove(10);

    // Root should now be 65
    if(myStreak.m_root->getID() != 65){
        return false;
    }

    // Left of the root should be 59
    if(myStreak.m_root->m_left->getID() != 59){
        return false;
    }

    // Right of the root should be 69
    if(myStreak.m_root->m_right->getID() != 69){
        return false;
    }

    return true;
}

bool Tester::removeLeftLeftRebalance(Streak &myStreak){
    Tiger newTiger = Tiger(5, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(4, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger4 = Tiger(3, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);

    myStreak.remove(10);

    // Root should now be 4
    if(myStreak.m_root->getID() != 4){
        return false;
    }

    // Left of the root should be 3
    if(myStreak.m_root->m_left->getID() != 3){
        return false;
    }

    // Right of the root should be 5
    if(myStreak.m_root->m_right->getID() != 5){
        return false;
    }

    return true;
}

bool Tester::removeLeftRightRebalance(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(25, CUB, MALE, DEAD);
    Tiger newTiger4 = Tiger(12, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);

    myStreak.remove(10);

    // Root should now be 15
    if(myStreak.m_root->getID() != 15){
        return false;
    }

    // Left of the root should be 12
    if(myStreak.m_root->m_left->getID() != 12){
        return false;
    }

    // Right of the root should be 25
    if(myStreak.m_root->m_right->getID() != 25){
        return false;
    }

    return true;
}

bool Tester::insertionRunsOLogN(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);

    clock_t start, end;
        Streak streak;
        int streakSize = 1000;
        int tempID = 0;
        int ID = 0;
        start = clock();
        for(int i=0;i<streakSize;i++){
            ID = idGen.getRandNum();
            if (i == streakSize / 2) tempID = ID;//we store this ID for later use
            Tiger tiger(ID,
                        static_cast<AGE>(ageGen.getRandNum()),
                        static_cast<GENDER>(genderGen.getRandNum()));
            streak.insert(tiger);
        }
        end = clock();

    clock_t start2, end2;
    
        Streak streak2;
        int streakSize2 = 2000;
        int tempID2 = 0;
        int ID2 = 0;
        start2 = clock();
        for(int i=0;i<streakSize2;i++){
            ID2 = idGen.getRandNum();
            if (i == streakSize2 / 2) tempID2 = ID2;//we store this ID for later use
            Tiger tiger(ID2,
                        static_cast<AGE>(ageGen.getRandNum()),
                        static_cast<GENDER>(genderGen.getRandNum()));
            streak2.insert(tiger);
        }
        end2 = clock();

    float T1 = end - start;
    float T2 = end2 - start2;

    float T3 = T2 / (2 * T1);

 
    if(T3 < 1.5 && T3 > 0.7){
        return true;
    }else{
        return false;
    }
}

bool Tester::removeNormalCase(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);

    myStreak.remove(10);

    // Root should now be 10. Left and right should be nullptr
    if(myStreak.m_root->getID() != 15 || myStreak.m_root->getLeft() != nullptr || myStreak.m_root->getRight() != nullptr){
        return false;
    }

    return true;  
}

bool Tester::removeEdgeCase(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(10, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);

    myStreak.remove(15);

    // Root should now be 10
    if(myStreak.m_root->getID() != 10){
        return false;
    }

    return true; 
}

bool Tester::removeErrorCase(Streak &myStreak){
    // Tree is empty. Should not contain a 10
    if(myStreak.find(10) == true){
        return false;
    }

    return true;
}

bool Tester::countTigerCubs(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, DEAD);
    Tiger newTiger2 = Tiger(16, CUB, MALE, DEAD);
    Tiger newTiger3 = Tiger(17, CUB, MALE, DEAD);
    Tiger newTiger4 = Tiger(18, YOUNG, MALE, DEAD);
    Tiger newTiger5 = Tiger(19, CUB, MALE, DEAD);
    Tiger newTiger6 = Tiger(20, YOUNG, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);
    myStreak.insert(newTiger5);
    myStreak.insert(newTiger6);


    if(myStreak.countTigerCubs() != 4){
        return false;
    }

    return true;
}

bool Tester::removeDead(Streak &myStreak){
    Tiger newTiger = Tiger(15, CUB, MALE, ALIVE);
    Tiger newTiger2 = Tiger(16, CUB, MALE, ALIVE);
    Tiger newTiger3 = Tiger(17, CUB, MALE, ALIVE);
    Tiger newTiger4 = Tiger(18, CUB, MALE, DEAD);
    Tiger newTiger5 = Tiger(19, CUB, MALE, DEAD);
    Tiger newTiger6 = Tiger(20, CUB, MALE, DEAD);

    myStreak.insert(newTiger);
    myStreak.insert(newTiger2);
    myStreak.insert(newTiger3);
    myStreak.insert(newTiger4);
    myStreak.insert(newTiger5);
    myStreak.insert(newTiger6);


    myStreak.removeDead();

    // Amount of tiger cubs left should be 3
    if(myStreak.countTigerCubs() != 3){
        return false;
    }

    return true;
}

bool Tester::removeRunsOLogN(){
    Random idGen(MINID,MAXID);
    Random ageGen(0,2);
    Random genderGen(0,2);

    
        clock_t start, end;
        Streak streak;
        int streakSize = 1000;
        int tempID = 0;
        int ID = 0;
        for(int i=0;i<streakSize;i++){
            ID = i;
            if (i == streakSize / 2) tempID = ID;//we store this ID for later use
            Tiger tiger(ID,
                        static_cast<AGE>(ageGen.getRandNum()),
                        static_cast<GENDER>(genderGen.getRandNum()));
            streak.insert(tiger);
        }

        start = clock();
        for(int i = 0; i < streakSize; i++){
            streak.remove(i);
        }
        end = clock();
    

    
        clock_t start2, end2;
        Streak streak2;
        int streakSize2 = 2000;
        int tempID2 = 0;
        int ID2 = 0;
        start2 = clock();
        for(int i=0;i<streakSize2;i++){
            ID2 = i;
            if (i == streakSize / 2) tempID2 = ID2;//we store this ID for later use
            Tiger tiger(ID2,
                        static_cast<AGE>(ageGen.getRandNum()),
                        static_cast<GENDER>(genderGen.getRandNum()));
            streak2.insert(tiger);
        }

        start2 = clock();
        for(int i = 0; i < streakSize2; i++){
            streak2.remove(i);
        }
        end2 = clock();
    

    float T1 = end - start;
    float T2 = end2 - start2;

    float T3 = T2 / (2 * T1);

    cout << "FLOAT: " << T3 << endl;

 
    if(T3 < 1.5 && T3 > 0.7){
        return true;
    }else{
        return false;
    }
}
