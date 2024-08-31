// UMBC - CMSC 341 - Fall 2022 - Proj2
#include "streak.h"

Streak::Streak(){
    // Building a new tree, set the root to be nullptr
    m_root = nullptr;
}

Streak::~Streak(){
    clear();
}

void Streak::insert(const Tiger& tiger){
    // If the ID is negative
    if(tiger.getID() < 0){
        //cout << "Can't insert a negative ID" << endl;
    }else{
        // Helper function
        m_root = insertHelper(m_root, tiger);  
    }
}

void Streak::clear(){
    // Clears the tree from the root
    clearTreeHelper(m_root);
}

void Streak::remove(int id){
    //cout << "FOUR" << endl;
    // If the ID exists
    if(find(id) == true){
        Tiger * theMovedNode = removeHelper(m_root, id);
        //cout << "themovednode: " << theMovedNode->getID() << endl;
        //cout << endl;
        //cout << endl;
       // display(false);

        //cout << "mrootgetid: " << m_root->getID() << endl;
    
        if(theMovedNode != nullptr){
            updateHeight(theMovedNode);
            if(checkImbalance(theMovedNode) != -1){
            theMovedNode = rebalance(theMovedNode);
            }
            updateHeight(theMovedNode);
        }

        //cout << m_root->m_left->getID();
     
        //display(false);

    // If ID does not exist
    }else{
        //cout << "That ID does not exist" << endl;
    }
}

void Streak::updateHeight(Tiger* aTiger){
    // If both a left and a right exist
    if(aTiger->getLeft() && aTiger->getRight()){
        // If the left side is taller than the right side
        if(aTiger->getLeft()->getHeight() >= aTiger->getRight()->getHeight()){
           // The new height is the left side + 1
           aTiger->setHeight(aTiger->getLeft()->getHeight() + 1);
        // If the sides are of equal length
        }else if(aTiger->getLeft()->getHeight() == aTiger->getRight()->getHeight()){
            // Adds the left side + 1
            aTiger->setHeight(aTiger->getLeft()->getHeight() + 1);
        }
        // If the right side is taller than the left side
        else{
          // The new height is the right side + 1
          aTiger->setHeight(aTiger->getRight()->getHeight() + 1);  
        }
    }
    // If only the left side exists
    else if(aTiger->getLeft()){
        // The new height is the left side + 1
        aTiger->setHeight(aTiger->getLeft()->getHeight() + 1);
    }
    // If only the right side exists
    else if(aTiger->getRight()){
        // The new height is the right side + 1
       aTiger->setHeight(aTiger->getRight()->getHeight() + 1);
    }
    // If there are no children on either side  
    else{
        // The height is 0
        aTiger->setHeight(0);
    }  
}

int Streak::checkImbalance(Tiger* aTiger){
    // If both a left and right child exist
    if(aTiger->m_left && aTiger->m_right){
        // If the left child is 2 or more bigger than the right child
        if(aTiger->m_left->getHeight() > (aTiger->m_right->getHeight() + 0)){
            // Return the difference of the 2 heights
            return (aTiger->m_left->getHeight() - aTiger->m_right->getHeight());
        // If the right child is 2 or more bigger than the left child
        }else if(aTiger->m_right->getHeight() > (aTiger->m_left->getHeight() + 0)){
            // Return the difference of the 2 heights
            return (aTiger->m_right->getHeight() - aTiger->m_left->getHeight()); 
        // If the 2 children are the same height or seperated by one
        }else{
            return -1;
        }
    // If only the left child exists
    }else if(aTiger->m_left && !aTiger->m_right){
        // If the left child has a height of 2 or greater
        if(aTiger->m_left->getHeight() > 0){
            // Return the left child's height
            return (aTiger->m_left->getHeight());
        // If the left child has a height of 1
        }else{
            return -1;
        }
    // If only the right child exists
    }else if(aTiger->m_right && !aTiger->m_left){
        //cout << "yo" << endl;
        // If the right child has a height of 2 or greater
        if(aTiger->m_right->getHeight() > 0){
            // Return the right child's height
            return (aTiger->m_right->getHeight());
        // If the right child has a height of 1
        }else{
            return -1;
        }
    // If neither the right or left child exist
    }else{
        return -1;
    }
}

Tiger* Streak::rebalance(Tiger* aTiger){
    //cout << "OKEY" << endl;

    // If left height is 2+ bigger than right height
    // Left imbalance -> rotate right

    // If left child and right child exists, and left is bigger by 2+
    if(aTiger->m_left && aTiger->m_right && aTiger->m_left->getHeight() > aTiger->m_right->getHeight() + 1){
        //cout << "ONE" << endl;

        // left-left case

        // If left-left exists and left-right exists, and left-left has a bigger height
        if(aTiger->m_left->m_left && aTiger->m_left->m_right && 
           aTiger->m_left->m_left->getHeight() >= aTiger->m_left->m_right->getHeight())
        {
            // Rotate the left child of aTiger up
            return rotateRight(aTiger);
        // If left-left exists and left-right does not exist
        }else if(aTiger->m_left->m_left && !aTiger->m_left->m_right){
            // Rotate the left child of aTiger up
            return rotateRight(aTiger);
        }


        // left-right case

        // If left-right exists and left-left exists, and left-right has a bigger height
        else if(aTiger->m_left->m_right && aTiger->m_left->m_left && 
           aTiger->m_left->m_right->getHeight() >= aTiger->m_left->m_left->getHeight()){
            // Rotate right child of aTiger->m_left up
            aTiger->m_left = rotateLeft(aTiger->m_left);
            // Rotate the left child of aTiger up
            return rotateRight(aTiger);
        // If left-right exists and left-left does not exist
        }else{
            // Rotate right child of aTiger->m_left up
            aTiger->m_left = rotateLeft(aTiger->m_left);
            // Rotate the left child of aTiger up
            return rotateRight(aTiger);
        }


    // If left child exists and right child does not exist, and left child is 2 or bigger
    }else if(aTiger->m_left && !aTiger->m_right && aTiger->m_left->getHeight() >= 1){
        //cout << "TWO" << endl;
        // left-left case


        // If left-left exists and left-right exists, and left-left has a bigger height
        if(aTiger->m_left->m_left && aTiger->m_left->m_right && 
           aTiger->m_left->m_left->getHeight() >= aTiger->m_left->m_right->getHeight())
        {
            // Rotate the left child of aTiger up
            return rotateRight(aTiger);
        // If left-left exists and left-right does not exist
        }else if(aTiger->m_left->m_left && !aTiger->m_left->m_right){
            // Rotate the left child of aTiger up
            return rotateRight(aTiger);
        }


        // left-right case

        // If left-right exists and left-left exists, and left-right has a bigger height
        else if(aTiger->m_left->m_right && aTiger->m_left->m_left && 
           aTiger->m_left->m_right->getHeight() >= aTiger->m_left->m_left->getHeight()){
            // Rotate right child of aTiger->m_left up
            aTiger->m_left = rotateLeft(aTiger->m_left);
            // Rotate the left child of aTiger up
            return rotateRight(aTiger);
        // If left-right exists and left-left does not exist
        }else{
            // Rotate right child of aTiger->m_left up
            aTiger->m_left = rotateLeft(aTiger->m_left);
            // Rotate the left child of aTiger up
            return rotateRight(aTiger);
        }
    }


    // If right height is 2+ bigger than left height
    // Right imbalance -> rotate left


    // If left child and right child exists, and right is bigger by 2+
    else if(aTiger->m_left && aTiger->m_right && aTiger->m_right->getHeight() > aTiger->m_left->getHeight() + 1){
        //cout << "THREE" << endl;

        // right-right case

        // If right-right exists and right-left exists, and right-right has a bigger height
        if(aTiger->m_right->m_right && aTiger->m_right->m_left && 
            aTiger->m_right->m_right->getHeight() >= aTiger->m_right->m_left->getHeight())
        {
            // Rotate the right child of aTiger up
            return rotateLeft(aTiger);
        // If right-right exists and right-left does not exist
        }else if(aTiger->m_right->m_right && !aTiger->m_right->m_left){
            // Rotate the right child of aTiger up
            return rotateLeft(aTiger); 
        }

        
        // right-left case


        // If right-right exists and right-left exists, and right-left has a bigger height
        else if(aTiger->m_right->m_right && aTiger->m_right->m_left && 
            aTiger->m_right->m_left->getHeight() >= aTiger->m_right->m_right->getHeight()){
            // Rotate left child of aTiger up
            aTiger->m_right = rotateRight(aTiger->m_right);
            // Rotate the right child of aTiger up
            return rotateLeft(aTiger);
        // If right-left exists and right-right does not
        }else{
            // Rotate left child of aTiger up
            aTiger->m_right = rotateRight(aTiger->m_right);
            // Rotate the right child of aTiger up
            return rotateLeft(aTiger);  
        }

    // If right child exists and left child does not exist, and right child is 2 or bigger
    }else if(aTiger->m_right && !aTiger->m_left && aTiger->m_right->getHeight() >= 1){
        //cout << "BRO BRO" << endl;
        //cout << "FOUR" << endl;
        // right-right case

        // If right-right exists and right-left exists, and right-right has a bigger height
        if(aTiger->m_right->m_right && aTiger->m_right->m_left && 
            aTiger->m_right->m_right->getHeight() >= aTiger->m_right->m_left->getHeight())
        {
            // Rotate the right child of aTiger up
            return rotateLeft(aTiger);
        // If right-right exists and right-left does not exist
        }else if(aTiger->m_right->m_right && !aTiger->m_right->m_left){
            //cout << "MHM" << endl;
            // Rotate the right child of aTiger up
            return rotateLeft(aTiger); 
        }

        
        // right-left case


        // If right-right exists and right-left exists, and right-left has a bigger height
        else if(aTiger->m_right->m_right && aTiger->m_right->m_left && 
            aTiger->m_right->m_left->getHeight() >= aTiger->m_right->m_right->getHeight()){
            // Rotate left child of aTiger up
            aTiger->m_right = rotateRight(aTiger->m_right);
            // Rotate the right child of aTiger up
            return rotateLeft(aTiger);
        // If right-left exists and right-right does not
        }else{
            // Rotate left child of aTiger up
            aTiger->m_right = rotateRight(aTiger->m_right);
            // Rotate the right child of aTiger up
            return rotateLeft(aTiger);  
        }
    }
    
    // No rotation needed
    else{
        return aTiger;
    }
}

void Streak::dumpTree() const {dump(m_root);}

void Streak::dump(Tiger* aTiger) const{
    if (aTiger != nullptr){
        cout << "(";
        dump(aTiger->m_left);//first visit the left child
        cout << aTiger->m_id << ":" << aTiger->m_height;//second visit the node itself
        dump(aTiger->m_right);//third visit the right child
        cout << ")";
    }
}

void Streak::listTigers() const {
    // Starting at the root
    listTigersHelper(m_root);
}

bool Streak::setState(int id, STATE state){
    // Pointer to the root
    Tiger * curr = m_root;
    
    // While we have not reached the end of the tree
    while(curr != nullptr){
        // If the tiger ID is less than the current tiger's ID, we go down and left
        if(id < curr->getID()){
            curr = curr->m_left;
        }
        // If the tiger ID is more than the current tiger's ID, we go down and right
        else if(id > curr->getID()){
            curr = curr->m_right;
        }
        // If the ID is equal, we found the tiger that we want
        else{
            // If the tiger is already the state we want to change it to
            if(state == curr->getState()){
                //cout << "The tiger is already that state!" << endl;
                return false;
            }
            // If the state of the tiger is different from the state we want to change it to
            else{
                curr->setState(state);
                return true;
            }
        }
    }
    // Reached the end of the tree, and did not find the tiger
    return false;
}

void Streak::removeDead(){
    int counter = 0;
    int amountDead = 0;

    // Counts the amount of dead tigers
    amountDead = countNumberDead(m_root);

    while(counter < amountDead){
        //cout << "ONE" << endl;
        removeDeadHelper(m_root);
        counter++;
    }


}

bool Streak::findTiger(int id) const {
   // Pointer to the root
    Tiger * curr = m_root;
    
    // While we have not reached the end of the tree
    while(curr != nullptr){
        // If the tiger ID is less than the current tiger's ID, we go down and left
        if(id < curr->getID()){
            curr = curr->m_left;
        }
        // If the tiger ID is more than the current tiger's ID, we go down and right
        else if(id > curr->getID()){
            curr = curr->m_right;
        }
        // If the ID is equal, we found the tiger that we want
        else{
            return true;
        }
    }
    // Reached the end of the tree, and did not find the tiger
    return false; 
}

int Streak::countTigerCubs() const{
    int totalAmountCubs = 0;

    totalAmountCubs = countTigerCubHelper(m_root);

    return totalAmountCubs;
}

void Streak::display_subtree(Tiger * p_current, bool verbose_leaves, int depth){
    if(m_root == nullptr){
        cout << "Tree is empty" << endl;
    }else{
        if(p_current != nullptr){
        display_subtree(p_current->getLeft(), verbose_leaves, depth + 1);

        for(int i = 0; i < depth; i++){
            cout << "\t";
        }
        //cout << "(" << p_current->getID() << ", " << p_current->getHeight() << ")" << endl;
        cout << "(" << p_current->getID() << ", " << p_current->getHeight() << ")" << endl;
        display_subtree(p_current->getRight(), verbose_leaves, depth + 1);
        }else{
            if(verbose_leaves == true){
                for(int i = 0; i < depth; i++){
                    cout << "\t";
                }
                cout << "null-leaf" << endl;
            }
        }
    }
}

void Streak::display(bool verbose_leaves){
    display_subtree(m_root, verbose_leaves, 0);
}

Tiger * Streak::insertHelper(Tiger * curr, const Tiger& tiger){

    // If reached end of tree
    if(curr == nullptr){
        // Insert new tiger
        Tiger * newTiger = new Tiger(tiger.getID(), tiger.getAge(), tiger.getGender(), tiger.getState());
        return newTiger;
    }

    // If tiger ID is less than the ID of the current tiger
    if(tiger.getID() < curr->getID()){
        // Go left on the tree
        curr->m_left = insertHelper(curr->getLeft(), tiger);

        // Refresh the height
        updateHeight(curr);
        // If there is an imbalance
        if(checkImbalance(curr) != -1){
            curr = rebalance(curr);
        }
        //p_current = rebalance(p_current);
        // Refresh heights again if there was a rebalance
        updateHeight(curr);

    // If tiger ID is more than the ID of the current tiger
    }else if(tiger.getID() > curr->getID()){
         // Go right on the tree
        curr->m_right = insertHelper(curr->getRight(), tiger);

        // Refresh the height
        updateHeight(curr);
        if(checkImbalance(curr) != -1){
            curr = rebalance(curr);
        }
        // Refresh heights again if there was a rebalance
        updateHeight(curr);
    }else{
        //cout << "That ID already exists" << endl;
    }

    return curr;
}

Tiger * Streak::rotateLeft(Tiger * curr){
    if(curr == m_root){
        Tiger * temp =  curr->m_right->m_left;
        Tiger * right = curr->m_right;
        m_root = right;
        right->m_left = curr;
        curr->m_right = temp;
        updateHeight(right->m_left);
        updateHeight(right);
        return right;
    }else{
        Tiger * temp =  curr->m_right->m_left;
        Tiger * right = curr->m_right;
        right->m_left = curr;
        curr->m_right = temp;
        updateHeight(right->m_left);
        updateHeight(right);
        return right;
    }
}

Tiger * Streak::rotateRight(Tiger * curr){
    if(curr == m_root){
        Tiger * temp =  curr->m_left->m_right;
        Tiger * left = curr->m_left;
        m_root = left;
        left->m_right = curr;
        curr->m_left = temp;
        updateHeight(left->m_right);
        updateHeight(left);
        return left;
    }else{
        Tiger * temp =  curr->m_left->m_right;
        Tiger * left = curr->m_left;
        left->m_right = curr;
        curr->m_left = temp;
        updateHeight(left->m_right);
        updateHeight(left);
        return left; 
    }
    
}

int Streak::countTigerCubHelper(Tiger * curr) const{
    // If the tree is empty
    if(curr == nullptr){
        return 0;
    // If the tree is not empty
    }else{
        //cout << "CURR: " << curr->getID() << endl;
        // If the tiger is a cub
        if(curr->getAge() == 0){
            // Add 1 to the total
            return 1 + countTigerCubHelper(curr->getLeft()) + countTigerCubHelper(curr->getRight());
        // If the tiger is not a cub
        }else{
           return countTigerCubHelper(curr->getLeft()) + countTigerCubHelper(curr->getRight()); 
        }
    }
}

void Streak::clearTreeHelper(Tiger * curr){
    // If the tree is not empty
    if(curr != nullptr){
        clearTreeHelper(curr->getLeft());
        clearTreeHelper(curr->getRight());
        delete curr;
    }
}

void Streak::listTigersHelper(Tiger * curr) const{
    // InOrder traversal

    if(curr == nullptr){
        return;
    }

    listTigersHelper(curr->getLeft());

    cout << curr->getID() << ":";

    if(curr->getAge() == 0){
        cout << "CUB" << ":";
    }else if(curr->getAge() == 1){
        cout << "YOUNG" << ":";
    }else{
        cout << "OLD" << ":";
    }

    if(curr->getGender() == 0){
        cout << "MALE" << ":";
    }else if(curr->getGender() == 1){
        cout << "FEMALE" << ":";
    }else{
        cout << "UNKNOWN" << ":";
    }

    if(curr->getState() == 0){
        cout << "ALIVE";
    }else{
        cout << "DEAD";
    }

    cout << endl;

    listTigersHelper(curr->getRight());
}

bool Streak::find(int data){
    // At root of tree
    Tiger * curr = m_root;
    
    while(curr != nullptr){
        // If the ID is less than the current node's ID, we go down and left
        if(data < curr->getID()){
            curr = curr->getLeft();
        }
         // If the ID is more than the current node's ID, we go down and right
        else if(data > curr->getID()){
            curr = curr->getRight();
        }
        // If the data is equal to
        else{
            return true;
        }
    }
    // Reached nullptr and have not found value
    return false;
}


Tiger* Streak::removeHelper(Tiger * curr, int id){
    // If the tree is empty
    if (curr == nullptr){
        return curr;
    // If the tree is not empty
    }else{
        // If the ID to remove is not the root
        if(id != m_root->getID()){
            // If ID is smaller than root, go left
            if (id < curr->getID()){
                curr->m_left = removeHelper(curr->getLeft(), id);

                updateHeight(curr);
        
            // If ID is greater than root, go right
            }else if (id > curr->getID()){
                curr->m_right = removeHelper(curr->getRight(), id);

                updateHeight(curr);
        
            // If the ID matches, we delete
            }else {
                // Node has no child
                if (curr->m_left == nullptr && curr->m_right == nullptr){
                    //cout << "1" << endl;
                    delete curr;
                    curr = nullptr;
                    //cout << "CURR" << endl;
                    return curr;
                    //cout << "CURR2" << endl;
                } 
                // Node with only right child
                else if (curr->m_left == nullptr && curr->m_right != nullptr){
                    //cout << "2" << endl;
                    Tiger * temp = curr->m_right;
                    delete curr;
                    curr = nullptr;
                    return temp;
                // Node with only left child
                }else if (curr->m_left != nullptr && curr->m_right == nullptr) {
                    //cout << "3" << endl;
                    Tiger * temp = curr->m_left;
                    delete curr;
                    curr = nullptr;
                    return temp;
                // Node has 2 children
                }else{
                    //cout << "4" << endl;
                    //cout << "ID: " << curr->getID() << endl;

                    //cout << "HERE.5: " << endl;
                    //display(false);
                    //cout << endl;

                    // the case of two children
                    Tiger * temp = findMinNode(curr->m_right);
                    curr->setID(temp->getID());
                    curr->setAge(temp->getAge());
                    curr->setGender(temp->getGender());
                    curr->setState(temp->getState());

                    //curr->setHeight(curr->getHeight() - 1);

                   // curr->m_height
                   removeHelper2(curr->m_right, temp->getID(), curr, false);

                   // removeHelper2(curr->m_right, temp->getID());
                    
                    // Return node so the height can be changed
                    return curr;

                    
                }
            }
        // If the ID to remove is at the root
        }else{
            // If ID is smaller than root, go left
            if (id < curr->getID())
                curr->m_left = removeHelper(curr->getLeft(), id);
        
            // If ID is greater than root, go right
            else if (id > curr->getID())
                curr->m_right = removeHelper(curr->getRight(), id);
        
            // If the ID matches, we delete
            else {
                // Node has no child
                if (curr->m_left == nullptr && curr->m_right == nullptr){
                    //cout << "1" << endl;
                    delete curr;
                    curr = nullptr;
                    
                    m_root = nullptr;

                    return curr;
                } 
                // Node with only right child
                else if (curr->m_left == nullptr && curr->m_right != nullptr){
                    //cout << "2" << endl;
                    Tiger * temp = curr->m_right;
                    delete curr;
                    curr = nullptr;

                    m_root = temp;
                    m_root->m_right = temp->m_right;

                    return temp;
                // Node with only left child
                }else if (curr->m_left != nullptr && curr->m_right == nullptr) {
                    //cout << "3" << endl;
                    Tiger * temp = curr->m_left;
                    delete curr;
                    curr = nullptr;

                    m_root = temp;
                    m_root->m_left = temp->m_left;

                    return temp;
                // Node has 2 children
                }else{
                    //cout << "4" << endl;
                    //cout << "ID: " << curr->getID() << endl;

                    //cout << "HERE.5: " << endl;
                    //display(false);
                    //cout << endl;


                    Tiger * temp = findMinNode(curr->m_right);
                    curr->setID(temp->getID());
                    curr->setAge(temp->getAge());
                    curr->setGender(temp->getGender());
                    curr->setState(temp->getState());

                    //curr->setHeight(curr->getHeight() - 1);

                    m_root = curr;

                    removeHelper2(curr->m_right, temp->getID(), curr, false);

                    // Return node so the height can be changed
                    return curr;

                    
                }
            }
        }
    }
  
   //return nullptr; 
}


Tiger* Streak::findMinNode(Tiger * curr){
    // Going all the way left to find the smallest node
    while(curr->getLeft() != nullptr){
        curr = curr->getLeft();
    }

    return curr;
}

int Streak::countNumberDead(Tiger * curr){
    // If the tree is empty
    if(curr == nullptr){
        return 0;
    // If the tree is not empty
    }else{
        // If the tiger is dead
        if(curr->getState() == 1){
            // Add 1 to the total
            return 1 + countNumberDead(curr->getLeft()) + countNumberDead(curr->getRight());
        // If the tiger is not dead
        }else{
           return countNumberDead(curr->getLeft()) + countNumberDead(curr->getRight()); 
        }
    }
}

int Streak::removeDeadHelper(Tiger * curr){
    //cout << "TWO" << endl;
    // If the tree is empty
    if(curr == nullptr){
        return -1;
    // If the tree is not empty
    }else{
        // If the tiger is dead
        if(curr->getState() == 1){
            //cout << "THREE" << endl;
            // Remove the tiger
            remove(curr->getID());
            return -1;
        // If the tiger is not dead
        }else{
           return removeDeadHelper(curr->getLeft()) + removeDeadHelper(curr->getRight()); 
        }
    }
}

Tiger* Streak::removeHelper2(Tiger * curr, int id, Tiger * parent, bool coolBoolean){
    if (id < curr->getID()){
        curr = removeHelper2(curr->getLeft(), id, curr, true);
    }else{
        // << "booyuh" << endl;
        // Could have a right child
        if(curr->m_right != nullptr){
            curr->setAge(curr->m_right->getAge());
            curr->setGender(curr->m_right->getGender());
            curr->setID(curr->m_right->getID());
            curr->setState(curr->m_right->getState());
            curr->setHeight(curr->m_right->getHeight());

            delete curr->m_right;
            curr->m_right = nullptr;

            updateHeight(parent);

            /*
            if(coolBoolean == true){
                delete parent->m_left;
                parent->m_left = nullptr;
                updateHeight(parent);
            }else{
                delete parent->m_right;
                parent->m_right = nullptr;
                updateHeight(parent);
            }
            */

            return curr;
        // Does not have a right child
        }else{
            // << "booyuh 2" << endl;
            //cout << "curr->getID(): " << curr->getID() << endl;
            //delete m_root->m_right;
            //m_root->m_right = nullptr;
            delete curr;
            curr = nullptr;

            if(coolBoolean == true){
                delete parent->m_left;
                parent->m_left = nullptr;
                updateHeight(parent);
            }else{
                delete parent->m_right;
                parent->m_right = nullptr;
                updateHeight(parent);
            }

            //cout << "m_root->getID(): " << m_root->getID() << endl;
            return curr;
        }     
    }
        
    //return nullptr;
}

