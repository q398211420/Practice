/*
+----------------------+
| Tables_in_employees  |
+----------------------+
| current_dept_emp     |
| departments          |
| dept_emp             |
| dept_emp_latest_date |
| dept_manager         |
| employees            |
| myemp                |
| mysalaries           |
| salaries             |
| titles               |
+----------------------+
employees
+------------+---------------+------+-----+---------+-------+  
| Field      | Type          | Null | Key | Default | Extra |
+------------+---------------+------+-----+---------+-------+
| emp_no     | int(11)       | NO   | PRI | NULL    |       |
| birth_date | date          | NO   |     | NULL    |       |
| first_name | varchar(14)   | NO   |     | NULL    |       |
| last_name  | varchar(16)   | NO   |     | NULL    |       |
| gender     | enum('M','F') | NO   |     | NULL    |       |
| hire_date  | date          | NO   |     | NULL    |       |
+------------+---------------+------+-----+---------+-------+
current_dept_emp 
+-----------+---------+------+-----+---------+-------+
| Field     | Type    | Null | Key | Default | Extra |
+-----------+---------+------+-----+---------+-------+
| emp_no    | int(11) | NO   |     | NULL    |       |
| dept_no   | char(4) | NO   |     | NULL    |       |
| from_date | date    | YES  |     | NULL    |       |
| to_date   | date    | YES  |     | NULL    |       |
+-----------+---------+------+-----+---------+-------+
*/
SELECT emp_no,dept_no FROM current_dept_emp WHERE dept_no IN (SELECT dept_no FROM current_dept_emp WHERE emp_no = 10008) LIMIT 20;