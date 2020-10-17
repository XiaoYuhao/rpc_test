#include <cstdlib>
#include <arpa/inet.h>

const u_int8_t PROCEDURE_CALL       = 0x01;
const u_int8_t PROCEDURE_RES        = 0x02;

const u_int8_t PROCEDURE_ERROR      = 0x91;
const u_int8_t PROCEDURE_NOT_FOUND  = 0x92;
const u_int8_t PROCEDURE_SUCCESS    = 0x01;

struct package_header{
    u_int8_t package_type;
    u_int8_t package_seq;
    u_int16_t package_length;
};

struct procedure_call_package{
    package_header header;
    u_int32_t procedure_id;
    u_int32_t para1;
    u_int32_t para2;
    procedure_call_package(){}
    procedure_call_package(u_int32_t id, u_int32_t p1, u_int32_t p2){
        header.package_type = PROCEDURE_CALL;
        header.package_seq = 0;
        header.package_length = htons(sizeof(procedure_call_package));
        procedure_id = htonl(id);
        para1 = htonl(p1);
        para2 = htonl(p2);
    }
    void setdata(u_int32_t id, u_int32_t p1, u_int32_t p2){
        header.package_type = PROCEDURE_CALL;
        header.package_seq = 0;
        header.package_length = htons(sizeof(procedure_call_package));
        procedure_id = htonl(id);
        para1 = htonl(p1);
        para2 = htonl(p2);
    }
    void tohost(){
        header.package_length = ntohs(header.package_length);
        procedure_id = ntohl(procedure_id);
        para1 = ntohl(para1);
        para2 = ntohl(para2);
    }
};

struct procedure_result_package{
    package_header header;
    u_int8_t status;
    u_int32_t result;
    procedure_result_package(){}
    procedure_result_package(u_int8_t _status, u_int32_t res){
        header.package_type = PROCEDURE_RES;
        header.package_seq = 0;
        header.package_length = htons(sizeof(procedure_result_package));
        status = _status;
        result = htonl(res);
    }
    void setdata(u_int8_t _status, u_int32_t res){
        header.package_type = PROCEDURE_RES;
        header.package_seq = 0;
        header.package_length = htons(sizeof(procedure_result_package));
        status = _status;
        result = htonl(res);
    }
    void tohost(){
        header.package_length = ntohs(header.package_length);
        result = ntohl(result);
    }
};