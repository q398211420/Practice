#!/bin/bash

# 设置数据库变量
DB_USER="root"           # 数据库用户名
DB_PASS="your_password"  # 数据库密码
DB_NAME="employees"      # 数据库名称
INPUT_FILE="SQLPractice.sql" # 输出文件名

# 执行 MySQL 查询并将结果输出到文件
mysql -u "$DB_USER" "$DB_NAME" --table < "$INPUT_FILE"

