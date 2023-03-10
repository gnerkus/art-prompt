//
// Created by Ifeanyi Oraelosi on 16.12.21.
//

#ifndef RPGDB_DB_DATABASEMANAGER_H
#define RPGDB_DB_DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager {
public:
  DatabaseManager();
  ~DatabaseManager();

  [[nodiscard]] bool isDatabaseOpen() const;
  QSqlDatabase getDatabase();
  bool initDatabase();
private:
  QSqlDatabase _database;

};

#endif //RPGDB_DB_DATABASEMANAGER_H
