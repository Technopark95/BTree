#include <iostream>


using namespace std;


int counter = 0;

struct btree {
    
    int number;
    int *keys;
    int n ;
    btree **C;
    bool leaf;
    
    
    btree(bool l)  {
    

    this->n = 0;
    this->leaf = l;
    this->keys =new int[3];
    this->C = new btree *[4];
    this->number = counter++;
   
    
 
}

    
    
    
}*root =NULL;



void splitChild( btree *x , int i) 
{ 
    btree * y = x->C[i];
    
    btree *z = new btree(true); 
    
    z->leaf = y->leaf;
    
    z->n = 1; 
  
    
    for (int j = 0; j < 1; j++) z->keys[j] = y->keys[j+2]; 
    
    
  
    if (y->leaf == false) 
    { 
        for (int j = 0; j < 2; j++) {
        z->C[j] = y->C[j+2]; 
        
        
    }
    
    
        
    } 
  
    
    for (int j = x->n; j >= i+1; j--) 
        x->C[j+1] = x->C[j]; 
  
    x->C[i+1] = z; 
   
    for (int j = x->n-1; j >= i; j--) 
        x->keys[j+1] = x->keys[j]; 
  
    
    x->keys[i] = y->keys[1]; 
  
     
    x->n = x->n + 1;
    
        y->n = 2 - 1; 
   
} 



void insertNonFull(btree * x , int k) 
{ 
    // Initialize index as index of rightmost element 
    int i = x->n-1; 
  
    // If this is a leaf node 
    if (x->leaf == true) 
    { 
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && x->keys[i] > k) 
        { 
            x->keys[i+1] = x->keys[i]; 
            i--; 
        } 
  
        // Insert the new key at found location 
        x->keys[i+1] = k; 
        x->n = x->n+1; 
    } 
    else // If this node is not leaf 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0 && x->keys[i] > k) 
            i--; 
            
            i = i+1;
  
        // See if the found child is full 
        if (x->C[i]->n == 3) 
        { 
            // If the child is full, then split it 
            splitChild( x,i); 
  
            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (x->keys[i] < k) 
                i++; 
        } 
        insertNonFull(x->C[i] ,k); 
    } 
} 


void insert(int k)  {
    
    btree * x = root;
    
    
    if (root == NULL) {
        
        root = new  btree(true); 
        root->keys[0] = k;  
        root->n = 1;
        
    }
    
    
     else 
    { 
        
        if (x->n == 3) 
        { 
            
            btree *s = new  btree(false); 

            root = s; 
            
            s->leaf = false;
            s->n= 0;
            s->C[0] = x;
  
            splitChild(s, 0); 

            insertNonFull(s,k); 
  
            
        } 
        else  insertNonFull(x,k); 
    } 
    
    
    
}

void traverse(btree * r) 
{ 

    // There are n keys and n+1 children, traverse through n keys 
    // and first n children 
    int i; 
    for (i = 0; i < r->n; i++) 
    { 
        // If this is not leaf, then before printing key[i], 
        // traverse the subtree rooted with child C[i]. 
        if (r->leaf == false) 
            traverse(r->C[i]); 
            
            
        cout << " " << r->keys[i]; 
       
    } 
  
    // Print the subtree rooted with last child 
    if (r->leaf == false) {
        
  
        traverse(r->C[i]); 
          
    } 
    

    
}



int main ()  {
    
   // for(int i = 1; i <= 10; i++) insert(i);
   
   insert(10); 
    insert(20); 
    insert(5); 
    insert(6); 
    insert(12); 
    insert(30); 
    insert(7); 
    insert(17);

traverse(root);

}


