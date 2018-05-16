#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct bstnode{
int data;
bstnode *left;
bstnode *right;
int height;
};

int gethight(bstnode *temp){
if(temp==NULL){
    return -1;
}

return temp->height;


}

bstnode *getnewnode(int data){
bstnode *newnode = new bstnode;
newnode->data = data;
newnode->left = NULL;
newnode->right = NULL;
newnode->height =0;
     return newnode;
}

void preordertraversal(bstnode *r){
if(r==NULL)
    return;
cout<<r->data<<"  "<<r->height<<endl;
preordertraversal(r->left);
preordertraversal(r->right);
}

void inordertraversal(bstnode *r){
if(r==NULL)
    return;
inordertraversal(r->left);
cout<<r->data<<"  ";
inordertraversal(r->right);
}

void postordertraversal(bstnode *r){
if(r==NULL)
    return;
postordertraversal(r->left);
postordertraversal(r->right);
cout<<r->data<<"  ";
}


void tolevelordertraversal(bstnode *r){
   if(r==NULL)
    return;
   queue<bstnode *> q;
   q.push(r);
   while(!q.empty()){
    bstnode *cur = q.front();
    cout<<cur->data<<"  "<<cur->height<<endl;
    if(cur->left!=NULL) q.push(cur->left);
    if(cur->right!=NULL) q.push(cur->right);
    q.pop();
   }
}

bstnode* leftrotate(bstnode *root){
   bstnode *childroot = root->right;
   bstnode *temp = childroot->left;

   childroot->left = root;
   root->right = temp;

   root->height = max(gethight(root->left),gethight(root->right))+1;
   childroot->height = max(gethight(childroot->left),gethight(childroot->right))+1;

   return childroot;
}

bstnode* rightrotate(bstnode *root){
   bstnode *childroot = root->left;
   bstnode *temp = childroot->right;

   childroot->right = root;
   root->left = temp;

   root->height = max(gethight(root->left),gethight(root->right))+1;
   childroot->height = max(gethight(childroot->left),gethight(childroot->right))+1;

   return childroot;
}

int getdifference(bstnode *root){
if(root==NULL)
    return 0;
return (gethight(root->left) - gethight(root->right));
}

bstnode* insert(bstnode *root,int data){
if(root==NULL){
   return getnewnode(data);

}
else if(data>((root)->data)){
    root->right = insert((root)->right,data);
}
else if(data<(root)->data)
    {
    root->left = insert((root)->left,data);
}
else{
    return root;
}

(root)->height = max(gethight((root)->left),gethight((root)->right))+1;

if(getdifference(root)>1){
        //left
    if(data<(root)->left->data){
        //left left
        return rightrotate(root);
        }
    else if(data>(root)->left->data){
        //left right
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }
}
else if(getdifference(root)<-1){
    //right
    if(data>(root)->right->data){
        //right right
        return leftrotate(root);
    }
    else if(data<(root)->right->data){
        //right left
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }
}
   return root;
}

bstnode* tosearch(bstnode *r,int data){
if(r==NULL)
    return NULL;
else if(r->data == data)
    return r;
else if(data <r->data)
    return tosearch(r->left,data);
else
    return tosearch(r->right,data);
}

bstnode *findmin(bstnode *r){
    bstnode *temproot = r;
while(temproot->left!=NULL){
    temproot = temproot->left;
}
return temproot;
}

bstnode *Delete(bstnode *r,int data){
if(r==NULL){
    return NULL;
}
else if(data > r->data){
    r->right = Delete(r->right,data);
}
else if(data < r->data){
    r->left = Delete(r->left,data);
}
else{
    if(r->left == NULL && r->right == NULL){
        delete r;
        r=NULL;
        return r;
    }
    else if(r->left==NULL){
        bstnode *temp = r;
        r = r->right;
        delete temp;
        return r;
    }
    else if(r->right==NULL){
        bstnode *temp = r;
        r = r->left;
        delete temp;
        return r;
    }
     else{
        bstnode *temp = findmin(r->right);
        r->data = temp->data;
        r->right = Delete(r->right,temp->data);
        return r;
     }
}
    r->height = 1 + max(gethight(r->left),gethight(r->right));
    if(getdifference(r)>1){
        //left
    if(getdifference(r->left)>=0){
        //left left
        return rightrotate(r);
    }
    else{
        //left right
        r->left = leftrotate(r->left);
        return rightrotate(r);
    }
 }
  else if(getdifference(r)<-1){
    //right
    if(getdifference(r->right)<=0){
        //right right
        return leftrotate(r);
    }
    else{
        //right left
        r->right = rightrotate(r->right);
        return leftrotate(r);
    }
}
   return r;

}




int main()
{
    bstnode *root = NULL;
      root =insert(root,30);
      root =insert(root,50);
      root =insert(root,20);
      root =insert(root,3122);
      root =insert(root,40);
      root =insert(root,4);
     root =insert(root,3);
           root =insert(root,14);
     root =insert(root,25);
     //root=Delete(root,20);
     //root=Delete(root,14);
     Delete(root,3);
/////////////////////////////////
//      root =insert(root,50);
//      root =insert(root,60);
//      root =insert(root,70);
     // root =insert(root,80);

    //tolevelordertraversal(root);
    cout<<endl;
    preordertraversal(root);





    return 0;
}
