/*
   文件读取内容

   文件一 teacher.txt

                     教师信息                  课程及学分...
            | id | name | academy | name | credit | flag | name | credit | flag |...

   文件二 student.txt

                     学生信息                  课程及分数...
            | id | name |  class  | name |  score | name |  score |...

 */

MainWindow::
            vector<person *>all_person:所有个人信息
            vector<course *>all_course:所有课程信息

student:: id, name, class
          map<int, int>course_id 存储课程id及分数

teacher:: id, name, academy
          map<int, int> course_id 存储课程id及学分

 course:: id, name, credit
          map<int, int> student_id 存储学生id及分数
