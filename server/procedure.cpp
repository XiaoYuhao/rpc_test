#include "procedure.h"

Call_Table* Call_Table::create(){
    if(_instance == NULL){
        _instance = new Call_Table;
    }
     return _instance;
}

int Call_Table::add_procedure(int id, Procedure pro){
    table[id] = pro;
    return 1;
}

int Call_Table::del_procedure(int id){
    table.erase(id);
}

int Call_Table::find_procedure(Procedure &p, int id){
        if(table.count(id)){
            p = table[id];
            return 1;
        }
        return 0;
    }
