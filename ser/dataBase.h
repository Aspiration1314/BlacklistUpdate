#ifndef _DATABASE_H_
#define _DATABASE_H_
#include<iostream>
#include<mysql/mysql.h>
#include<string.h>
#include<json/json.h>

using namespace std;

pthread_mutex_t dmut;
class dataBase
{
public:
    static dataBase* getDataBase()
    {
        cout<<"getDataBase()"<<endl;

        if(NULL == _dataBase)
        {
            pthread_mutex_lock(&dmut);
            if(NULL == _dataBase)
            {
                _dataBase = new dataBase();
            }
            pthread_mutex_unlock(&dmut);
        }
        return _dataBase;
    }
    
    bool insertIntoUserList(Json::Value& val)
    {
        cout<<"this is dataBase.insertIntoUserList()"<<endl;
        //insert into userlist values('zhangling','12345');
        char cmd[100] = "insert into userlist values('";
        strcat(cmd,val["NAME"].asString().c_str());
        strcat(cmd,"','");
        strcat(cmd,val["ID"].asString().c_str());
        strcat(cmd,"');");
        //mysql_real_query(_mpcon,cmd,strlen(cmd));
        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr<<"0 query fail;errno:"<<errno<<endl;
            return 0;
        }
        return true;
    }
    
    bool enrollIntoRootList(Json::Value& val)
    {
        cout<<"this is dataBase.enrollIntorootList()"<<endl;

        //<<val["NAME"].asString()<<endl;
        //cout<<val["PW"].asString()<<endl;

        char cmd[100] = "insert into rootlist values('";
        strcat(cmd,val["NAME"].asString().c_str());
        strcat(cmd,"','");
        strcat(cmd,val["PW"].asString().c_str());
        strcat(cmd,"');");
        //cout<<"111111"<<endl;

        //mysql_real_query(_mpcon,cmd,strlen(cmd));
        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr<<"0 query fail;errno:"<<errno<<endl;
            return 0;
        }
        return true;
    }
    //bool loginIntorootList(Json::Value& val)
    //{
        //char cmd[100] = "insert into rootlist values('";
        //strcat(cmd,val["NAME"].asString().c_str());
        //strcat(cmd,"','");
        //strcat(cmd,val["PW"].asString().c_str());
        //strcat(cmd,strcat(cmd,"');") );
        //mysql_real_query(_mpcon,cmd,strlen(cmd));
        //return true;
    //}
    //bool selectFromRootList(string& name,string& pw)
    //bool selectFromRootList(string& name,string& pw)
    bool loginIntorootList(Json::Value& val)
    //bool loginIntorootList(string& name,string& pw)
    {
        cout<<"this is dataBase.loginIntorootList()"<<endl;
        //cout<<name<<endl;
        //cout<<pw<<endl;

        //cout<<val["NAME"].asString()<<endl;
        //cout<<val["PW"].asString()<<endl;

        char cmd[100] = "select * from rootlist where name ='";
        strcat(cmd,val["NAME"].asString().c_str());
        strcat(cmd,"';");
        //mysql_real_query(_mpcon,cmd,strlen(cmd));
        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr<<"0 query fail;errno:"<<errno<<endl;
            return 0;
        }

        mp_res = mysql_store_result(_mpcon);
        bool result = false;
      
        while(mp_row = mysql_fetch_row(mp_res))
        {
            
            result = strcmp(mp_row[1],val["PW"].asString().c_str()) == 0;
        }
        mysql_free_result(mp_res);
        return result;
    }
    //bool selectFromUserList(string& id)
    bool selectFromUserList(Json::Value& val, char* str)
    {
        cout<<"this is dataBase.selectFromUserList()"<<endl;

        char  cmd[100] = "select * from userlist where id ='";
        strcat(cmd,val["ID"].asString().c_str());
        strcat(cmd,"';");

        if(mysql_real_query(_mpcon,cmd,strlen(cmd)))
        {
            cerr<<"0 query fail;errno:"<<errno<<endl;
            return 0;
        }
        mp_res = mysql_store_result(_mpcon);
        bool result = false;
       
        while(mp_row = mysql_fetch_row(mp_res))
        {
            //cout<<"name:"<<mp_row[0]<<"   "<<"id:"<<mp_row[1]<<endl;
            strcat(str,mp_row[0]);
            strcat(str,"    ");
            strcat(str,mp_row[1]);
            result = true;
        }
        mysql_free_result(mp_res);
        return result;
    }

    ~dataBase()
    {
        mysql_close(_mpcon);    
    }


private:
    dataBase()
    {
        cout<<"dataBase()"<<endl;
        _mpcon = mysql_init((MYSQL*)0);
        //mysql_real_connect(_mpcon,"127.0.0.1","root","111111",NULL,3306,NULL,0);
        if(!mysql_real_connect(_mpcon, "127.0.0.1", "root", "111111" , NULL, 3306, NULL, 0) )    //如果连接失败，则直接退出
        {
            cerr<<"mysql connect fail;errno:"<<errno<<endl;
            exit(0);        
        }
        //mysql_select_db(_mpcon,"blacklist");
        if(mysql_select_db(_mpcon,"blacklist") )
        {
            cerr<<"blacklist select fail:errno:"<<errno<<endl;
            exit(0);    
        }

        cout<<"数据库选择完成!"<<endl;
    }
    static dataBase* _dataBase;
    MYSQL* _mpcon;
    MYSQL_RES* mp_res;
    MYSQL_ROW mp_row;

};
dataBase* dataBase::_dataBase = NULL;

#endif
