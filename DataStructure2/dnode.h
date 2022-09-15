//
//  dnode.h
//  DataStructure2
//
//  Created by Minho Lee on 2021/11/07.
//

#ifndef dnode_h
#define dnode_h

using namespace std;

template<class Vtype>//have to check it. vtype means valuetype
class dnode
{
public:
    typedef Vtype value_type;
    
    dnode(const value_type& init_data = value_type(),dnode<Vtype>* init_fore = NULL,dnode<Vtype>* init_back = NULL)
    {
        data_field = init_data;
        link_fore = init_fore;
        link_back = init_back;
    }//constructor
    
    void set_data(const value_type& new_data){this->data_field = new_data;}//data setter
    void set_fore(dnode<Vtype>* new_fore){link_fore = new_fore;}
    void set_back(dnode<Vtype>* new_back){link_back = new_back;}
    
    value_type data() const {return data_field;}//get current data
    const dnode<Vtype>* fore() const{return link_fore;}//get fore link
    dnode<Vtype>* fore() {return link_fore;}
    const dnode* back() const{return link_back;}//get back link
    dnode<Vtype>* back() {return link_back;}
    
    
public:
    
    
private:
    value_type data_field;
    dnode<Vtype>* link_fore;
    dnode<Vtype>* link_back;
    
};//end node class for double link

template<class Vtype>
size_t list_length(dnode<Vtype>* head_ptr)
{
    const dnode<Vtype> *cursor;

            size_t answer;
            answer = 0;
            for (cursor = head_ptr; cursor != NULL; cursor = cursor->fore( ))
                ++answer;
            return answer;
}

template<class Vtype>
void list_head_insert(dnode<Vtype>*& head_ptr,const Vtype& entry)
{
    head_ptr = new dnode<Vtype>(entry,head_ptr,NULL);
}

template<class Vtype>
void list_tail_insert(dnode<Vtype>*& tail_ptr,const Vtype& entry)
{
    tail_ptr = new dnode<Vtype>(entry,tail_ptr,NULL);
}


template<class Vtype>
void list_insert(dnode<Vtype>* previous_ptr, const Vtype& entry)
{
    dnode<Vtype> *insert_ptr;
    insert_ptr = new dnode<Vtype>(entry,previous_ptr->fore(),previous_ptr);
    
    if(previous_ptr->fore()!=NULL)
        previous_ptr->fore()->set_back(insert_ptr);
    
    previous_ptr->set_fore(insert_ptr);
}//check again

template<class Vtype>
dnode<Vtype>* list_search(dnode<Vtype>* head_ptr, const Vtype& target)
{
    dnode<Vtype> *cursor;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->fore())
        if (target == cursor->data())
            return cursor;
    return NULL;
}

template<class Vtype>
const dnode<Vtype>* list_search(const dnode<Vtype>* head_ptr, const Vtype& target)
{
    const dnode<Vtype> *cursor;
    
    for(cursor = head_ptr  ;cursor!=NULL;cursor = cursor -> fore())
        if(target == cursor-> data())
            return cursor;
    return NULL;
}



//
template<class Vtype>
dnode<Vtype>* list_locate(dnode<Vtype> head_ptr, size_t position)
{
    dnode<Vtype> *cursor;
    size_t i;
    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != NULL); i++)
        cursor = cursor->fore( );

    return cursor;

  }


template<class Vtype>
const dnode<Vtype>* list_locate(const dnode<Vtype>* head_ptr, size_t position)
{
    const dnode<Vtype> *cursor;
    size_t i;
    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != NULL); i++)
        cursor = cursor->fore( );

    return cursor;
}


template<class Vtype>
void list_head_remove(dnode<Vtype>*& head_ptr)
{

    dnode<Vtype> *remove_ptr;
    remove_ptr = head_ptr;
    head_ptr = head_ptr->fore( );
    if (head_ptr != NULL)
        head_ptr->set_back(NULL);
    delete remove_ptr;
}


template<class Vtype>
void list_remove(dnode<Vtype>* previous_ptr)

{
    dnode<Vtype> *remove_ptr;
    remove_ptr = previous_ptr->fore( );
    previous_ptr->set_fore( remove_ptr->fore( ) );
    if (remove_ptr->fore() != NULL)
        remove_ptr->fore()->set_back(previous_ptr);
    delete remove_ptr;
}


template<class Vtype>
void list_clear(dnode<Vtype>*& head_ptr)
{
    while (head_ptr != NULL)
        list_head_remove(head_ptr);
}


template<class Vtype>
void list_copy(const dnode<Vtype>* source_ptr, dnode<Vtype>*& head_ptr, dnode<Vtype>*& tail_ptr)
{

    head_ptr = NULL;
    tail_ptr = NULL;
    if (source_ptr == NULL)
        return;
    list_head_insert(head_ptr, source_ptr->data( ));
    tail_ptr = head_ptr;

    source_ptr = source_ptr->fore( );
    while (source_ptr != NULL)
    {
        list_insert(tail_ptr, source_ptr->data( ));
        tail_ptr = tail_ptr->fore( );
        source_ptr = source_ptr->fore( );
    }
    
}


#endif /* dnode_h */
