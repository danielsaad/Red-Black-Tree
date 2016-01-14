#incl
namespace algorithms {
template <class T>
class rb_tree{
public:
    rb_tree(){
        m_root = nullptr;
    }

    rb_tree* root(){
        return m_root;
    }

    void left_rotate(rb_node* x){
        rb_node* y = x->m_children[1];
        x->m_children[1] = y->m_children[0];
        if(y->m_children[0]!=nullptr){
            y->m_children[0]->m_parent = x;
        }
        y->m_parent = x->m_parent;
        if(y->father()==nullptr){ //update root;
            m_root = y;
        }
        else if(x->father()->m_children[0] == x){
            x->father()->m_children[0] = y;
        }
        else{
            x->father()->m_children[1] = y;
        }
        y->m_children[0] = x;
        x->m_parent = y;
    }

    void right_rotate(rb_node* x){
        rb_node* y = x->m_children[0];
        x->m_children[0] = y->m_children[1];
        if(y->m_children[1]!=nullptr){
            y->m_children[1]->m_parent = x;
        }
        y->m_parent = x->father();
        if(y->m_parent==nullptr){
            m_root = y;
        }
        else if(x->father()->m_children[0]==x){
            x->father()->m_children[0] = y;
        }
        else{
            x->father()->m_children[1] = y;
        }
        y->m_children[1] = x;
        x->m_parent = y;
    }

    void insert(const T& data){
        rb_node* z = new rb_node(data);
        rb_node* x = m_root;
        rb_node* y = nullptr;
        while(x!=nullptr){
            y = x;
            if(data < x->data){
                x = x->m_childred[0];
            }
            else{
                x = x->m_children[1];
            }
        }
        z->m_parent = y;
        if(y==nullptr){
            m_root = z;
        }
        else if(z->m_data < y->m_data){
            y->m_children[0] = z;
        }
        else{
            y->m_children[1] = z;
        }
        fix_properties(z);
    }
private:
    rb_node* m_root;
    void fix_properties(rb_node* z){
        while(z->father()->is_red()){
            rb_node* y = z->uncle();
            if(y->is_red()){ //we can flip the colors
                y->m_red = false;
                z->father()->m_red = false;
                z->grandfather()->m_red = true;
                z = z->grandfather();
            }
            else{
                if(z==z->father()->m_children[1]){
                    z = z->father();
                    left_rotate(z);
                }
                z->father()->m_red = false;
                z->grandfather()->m_red = true;
                right_rotate(z->grandfather());
            }
        }
        m_root->m_red = false; //root is always black
    }

};

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

    bool is_red(const rb_tree* v){
        if(v!=nullptr && v->m_red){
            return true;
        }
        return false;
    }

    rb_node* father(){
        return m_parent;
    }

    rb_node* grandfather(){
        if(m_parent!=nullptr){
            return(m_parent->m_parent);
        }
        return nullptr;
    }
    rb_node* uncle(){
        if(m_parent!=nullptr){
            if(m_parent->m_children[0] == this){
                return m_parent->m_children[1];
            }
            else{
                return m_parent->m_children[0];
            }
        }
        return nullptr;
    }

    bool m_red;
    T m_data;
    rb_node<T>* m_children[2];
    rb_node* m_parent;

    friend class rb_tree;
};



} //end namespace algorithms
