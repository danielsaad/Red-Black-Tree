#include <iostream>
#include <cassert>
using namespace std;

namespace algorithms {

template<class T> class rb_node;
template<class T> class rb_tree;

template <class T>
class rb_node{
public:
    rb_node(T data):m_data(data){
        m_red = true;
        m_children[0] = nullptr;
        m_children[1] = nullptr;
        m_parent = nullptr;
    }
private:

    bool m_red;
    T m_data;
    rb_node<T>* m_children[2];
    rb_node* m_parent;

    friend class rb_tree<T>;
};





template <class T>
class rb_tree{
public:
    rb_tree(){
        m_root = nullptr;
    }

    rb_node<T>* root(){
        return m_root;
    }

    void print(rb_node<T>* v){
        if(v!=nullptr){
            print(left(v));
            cout << v->m_data << "\n";
            print(right(v));
        }
    }

    bool assert_properties(){
        if(assert_bst(m_root) && assert_root_color() && assert_red_violation(m_root) && assert_black_violation(m_root)){
            return true;
        }

        return false;
    }

    bool assert_root_color(){
        if(!is_red(m_root)){
            return true;
        }
        return false;
    }

    bool assert_bst(rb_node<T>* v){
        rb_node<T> *l,*r;
        l = left(v);
        r = right(v);
        if(v!=nullptr){
            if(l!=nullptr){
                if(v->m_data < l->m_data ){
                    return false;
                }
            }
            if(r!=nullptr){
                if(v->m_data > r->m_data){
                    return false;
                }
            }
            if(!assert_bst(l) || !assert_bst(r)){
                return false;
            }
        }
        return true;
    }

    bool assert_red_violation(rb_node<T>* x){
        if(x!=nullptr){
            if(is_red(x) && (is_red(left(x)) || is_red(right(x)))){
                return false;
            }
            if(!assert_red_violation(left(x))){
                return false;
            }
            if(!assert_red_violation(right(x))){
                return false;
            }
        }
        return true;
    }

    bool assert_black_violation(rb_node<T>* root){
        if(root!=nullptr){
            if(black_height(left(root))!=black_height(right(root))){
                return false;
            }
            if(!assert_black_violation(left(root))){
                return false;
            }
            if(!assert_black_violation(right(root))){
                return false;
            }
        }
        return true;
    }

    size_t black_height(rb_node<T>* root){
        if(root == nullptr){
            return 0;
        }
        else{
            size_t v = 0;
            if(!is_red(root)){
                v = 1;
            }
            return v + max(black_height(left(root)),black_height(right(root)));
        }
    }

    void left_rotate(rb_node<T>* x){
        rb_node<T>* y = right(x);
        right(x) = left(y);
        if(left(y)!=nullptr){
            father(left(y))=x;
        }
        father(y) = father(x);
        if(father(y)==nullptr){ //update root;
            m_root = y;
        }
        else if(left(father(x)) == x){
            left(father(x))=y;
        }
        else{
            right(father(x)) = y;
        }
        left(y) = x;
        father(x) = y;
    }

    void right_rotate(rb_node<T>* x){
        rb_node<T>* y = left(x);
        left(x) = right(y);
        if(right(y)!=nullptr){
            father(right(y))= x;
        }
        father(y) = father(x);
        if(father(y)==nullptr){
            m_root = y;
        }
        else if(left(father(x))==x){
            left(father(x)) = y;
        }
        else{
            right(father(x)) = y;
        }
        right(y) = x;
        father(x) = y;
    }

    void delete_node(rb_node<T>* z){
        rb_node<T>* y = z;
        rb_node<T>* x;
        bool y_original_color = z->m_red;
        if(left(z)==nullptr){
            x = right(z);
            transplant(z,right(z));
        }
        else if(right(z)==nullptr){
            x = left(z);
            transplant(z,left(z));
        }
        else{
            y = rb_minimum(right(z));
            y_original_color = y->m_red;
            x = right(y);
            if(father(y)==z){ //TODO: is this really necessary? x is alredy y's son.
                if(x!=nullptr){
                    father(x)=y;
                }
            }
            else{
                transplant(y,x);
                right(y) = right(z);
                father(right(y)) = y;
            }
            transplant(z,y);
            left(y) = left(z);
            father(left(y)) = y;
            y_original_color = z->m_red;
            if(y_original_color==false){
                rb_delete_fix_properties(x);
            }

        }
        delete z;
    }

    void rb_delete_fix_properties(rb_node<T>* x){
        while(x!=m_root && !is_red(x)){
            if(x == left(father(x))){
                rb_node<T>* w = right(father(x)); //w is x sibling
                if(is_red(w)){
                    w->m_red = false;
                    father(x)->m_red = true;
                    left_rotate(father(x));
                    w = right(father(x));
                }
                if(!is_red(left(w)) && !is_red(right(w))){ //both children of w are black
                    w->m_red = true;
                    x = father(x);
                }
                else{
                    if(!is_red(right(w))){
                        left(w)->m_red  = false;
                        w->m_red = true;
                        right_rotate(w);
                        w = right(father(x));
                    }
                    w->m_red = father(w->m_red);
                    father(x)->m_red = false;
                    right(w)->m_red = false;
                    left_rotate(father(x));
                    x = m_root; // end loop
                }
            }
            else{
                rb_node<T>* w = left(father(x)); //w is x sibling
                if(is_red(w)){
                    w->m_red = false;
                    father(x)->m_red = true;
                    right_rotate(father(x));
                    w = left(father(x));
                }
                if(!is_red(right(w)) && !is_red(left(w))){ //both children of w are black
                    w->m_red = true;
                    x = father(x);
                }
                else{
                    if(!is_red(left(w))){
                        right(w)->m_red  = false;
                        w->m_red = true;
                        left_rotate(w);
                        w = left(father(x));
                    }
                    w->m_red = father(w->m_red);
                    father(x)->m_red = false;
                    left(w)->m_red = false;
                    right_rotate(father(x));
                    x = m_root; // end loop
                }
            }
        }
        x->m_red = false;
    }

    rb_node<T>* rb_minimum(rb_node<T>* root){
        rb_node<T>* prev = root;
        while(root!=nullptr){
            prev = root;
            root = left(root);
        }
        return prev;
    }

    void transplant(rb_node<T>* u, rb_node<T>* v){
        if(father(u)==nullptr){
            m_root = v;
        }
        else if (u == left(father(u))){
            left(father(u)) = v;
        }
        else{
            right(father(u)) = v;
        }
        if(v!=nullptr){
            father(v) = father(u);
        }
    }

    void insert(T data){
        rb_node<T>* z = new rb_node<T>(data);
        rb_insert_node(z);
    }



    void rb_insert_node(rb_node<T>* z){
        rb_node<T>* x = m_root;
        rb_node<T>* y = nullptr;
        while(x!=nullptr){
            y = x;
            if(z->m_data < x->m_data){
                x = left(x);
            }
            else{
                x = right(x);
            }
        }
        z->m_parent = y;
        if(y==nullptr){
            m_root = z;
        }
        else if(z->m_data < y->m_data){
            left(y) = z;
        }
        else{
            right(y) = z;
        }
        rb_insert_fix_properties(z);
    }
private:
    rb_node<T>* m_root;

    bool is_red(rb_node<T>* v){
        if(v!=nullptr && v->m_red){
            return true;
        }
        return false;
    }

    void rb_insert_fix_properties(rb_node<T>* z){
        while(is_red(father(z))){
            if(father(z)==left(grandfather(z))){
                rb_node<T>* y = uncle(z);
                if(is_red(y)){ //we can flip the colors
                    y->m_red = false;
                    father(z)->m_red = false;
                    grandfather(z)->m_red = true;
                    z = grandfather(z);
                }
                else{
                    if(z==right(father(z))){
                        z = father(z);
                        left_rotate(z);
                    }
                    father(z)->m_red = false;
                    grandfather(z)->m_red = true;
                    right_rotate(grandfather(z));
                }
            }
            else{
                rb_node<T>* y = uncle(z);
                if(is_red(y)){ //we can flip the colors
                    y->m_red = false;
                    father(z)->m_red = false;
                    grandfather(z)->m_red = true;
                    z = grandfather(z);
                }
                else{
                    if(z==left(father(z))){
                        z = father(z);
                        right_rotate(z);
                    }
                    father(z)->m_red = false;
                    grandfather(z)->m_red = true;
                    left_rotate(grandfather(z));
                }
            }
        }
        m_root->m_red = false; //root is always black
    }
    rb_node<T>*& left(rb_node<T>*& v){
        if(v==nullptr){
            return v;
        }
        return v->m_children[0];
    }

    rb_node<T>*& right(rb_node<T>*& v){
        if(v==nullptr){
            return v;
        }
        return v->m_children[1];
    }

    rb_node<T>*& father(rb_node<T>*& v){
        if(v==nullptr){
            return v;
        }
        return(v->m_parent);
    }

    rb_node<T>*& grandfather(rb_node<T>*& v){
        return(father(father(v)));
    }
    rb_node<T>*& uncle(rb_node<T>*& v){
        rb_node<T>* g = grandfather(v);
        if(father(v)==left(g)){
            return(right(g));
        }
        else{
            return(left(g));
        }
    }
};


} //end namespace algorithms
