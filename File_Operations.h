#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void New_File(QString fileName);
void New_PasswdFile(QString fileName , QString passwd);
void empty_file(QString fileName);
void DeleteOneline(int nNum, QString &strall);
void deleteOnelineInFile(int nNumLine, QString filename);
void empty_file(QString fileName);
void DataMonitor_In_File(QString file , double time , double voltage , double current);

#endif // FILE_OPERATIONS_H
