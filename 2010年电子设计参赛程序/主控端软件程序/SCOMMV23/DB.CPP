

BOOL ODBCConnect(CString strDBFile)
{
    CString strConnect;
    strConnect.Format(_T("ODBC;DRIVER={MICROSOFT ACCESS DRIVER (*.mdb)};UID=sa;PWD=;DBQ=%s"), strDBFile);

    CDatabase db;
    if(db.Open(NULL, FALSE, FALSE, strConnect))
    {
        //连接数据库成功
        CRecordset rs(&db);
        CString strSql;
        strSql = _T("select * from info");                                //SQL语句
        rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSql);                        //执行Sql语句（可添加　删除　查询等）
        if(rs.IsOpen())
        {
            CDBVariant variant;
            rs.MoveFirst();
            while(!rs.IsEOF())
            {
                //读取记录
                rs.GetFieldValue(_T("姓名"), variant);

                rs.MoveNext();
            }
        }

        db.Close();
        return TRUE;
    }

    return FALSE;
}