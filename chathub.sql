-- MySQL dump 10.13  Distrib 8.0.22, for Win64 (x86_64)
--
-- Host: localhost    Database: chathub
-- ------------------------------------------------------
-- Server version	8.0.22

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES UTF8MB4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `t_chatmsg`
--

DROP TABLE IF EXISTS `t_chatmsg`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `t_chatmsg` (
  `f_id` bigint NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `f_senderid` bigint NOT NULL COMMENT '发送者id',
  `f_targetid` bigint NOT NULL COMMENT '接收者id',
  `f_msgcontent` varchar(128) NOT NULL COMMENT '聊天内容',
  `f_create_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '创建时间',
  `f_remark` varchar(64) DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`f_id`),
  KEY `f_id` (`f_id`)
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_chatmsg`
--

LOCK TABLES `t_chatmsg` WRITE;
/*!40000 ALTER TABLE `t_chatmsg` DISABLE KEYS */;
INSERT INTO `t_chatmsg` VALUES (1,0,1,'测试','2021-01-12 16:37:49',NULL),(2,0,2,'测试','2021-01-12 16:37:49',NULL),(3,0,3,'测试','2021-01-12 16:37:49',NULL),(4,0,4,'测试','2021-01-12 16:37:49',NULL),(5,0,5,'测试','2021-01-12 16:37:49',NULL),(6,2,0,'test','2021-01-12 17:24:41',NULL),(7,0,333,'tttt','2021-01-13 00:17:53',NULL),(8,1,222,'tttttt','2021-01-13 00:20:43',NULL),(9,1,1,'sda','2021-01-13 00:21:59',NULL),(10,1,0,'你好','2021-01-13 01:27:17',NULL),(11,0,1,'服务端测试\ntest','2021-01-13 01:44:09',NULL),(12,0,1,'','2021-01-13 01:44:09',NULL),(13,0,1,'','2021-01-13 01:45:05',NULL),(14,0,1,'测试~','2021-01-13 02:28:20',NULL),(15,1,2,'小明你好！','2021-01-13 02:38:27',NULL),(16,0,1,'test','2021-01-13 02:51:50',NULL),(17,1,0,'啊啊啊','2021-01-13 02:52:23',NULL),(18,1,0,'test','2021-01-13 02:55:30',NULL),(19,1,0,'','2021-01-13 02:55:30',NULL),(20,1,0,'test','2021-01-13 03:00:54',NULL),(21,1,0,'','2021-01-13 03:00:54',NULL),(22,1,0,'你好','2021-01-13 03:03:29',NULL),(23,0,6,'测试发送信息','2021-01-13 08:57:07',NULL),(24,0,7,'你好！','2021-01-13 09:22:42',NULL),(25,0,5,'你好\n1\n2\n3\n4\n5\n6\n7\n8\n1','2021-01-13 09:27:47',NULL),(26,0,6,'你好！\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n\n1\n1\n1','2021-01-13 09:36:16',NULL),(27,1,0,'你好','2021-01-13 09:42:01',NULL),(28,1,0,'你好','2021-01-13 09:42:10',NULL),(29,1,2,'测试\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n','2021-01-13 09:46:02',NULL),(30,1,0,'测试对在线用户发送消息','2021-01-13 09:51:24',NULL),(31,1,0,'测试','2021-01-13 09:51:50',NULL),(32,1,0,'测试','2021-01-13 09:54:50',NULL);
/*!40000 ALTER TABLE `t_chatmsg` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user`
--

DROP TABLE IF EXISTS `t_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `t_user` (
  `f_id` bigint NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `f_user_id` bigint NOT NULL COMMENT '用户ID',
  `f_username` varchar(64) NOT NULL COMMENT '用户名',
  `f_nickname` varchar(64) NOT NULL COMMENT '用户昵称',
  `f_password` varchar(64) DEFAULT NULL COMMENT '用户密码',
  `f_facetype` int DEFAULT '0' COMMENT '用户头像类型',
  `f_customface` varchar(32) DEFAULT NULL COMMENT '自定义头像名',
  `f_customfacefmt` varchar(6) DEFAULT NULL COMMENT '自定义头像格式',
  `f_gender` int DEFAULT '0' COMMENT '性别',
  `f_birthday` bigint DEFAULT '19900101' COMMENT '生日',
  `f_signature` varchar(256) DEFAULT NULL COMMENT '个性签名',
  `f_address` varchar(256) DEFAULT NULL COMMENT '地址',
  `f_phonenumber` varchar(64) DEFAULT NULL COMMENT '电话',
  `f_mail` varchar(256) DEFAULT NULL COMMENT '邮箱',
  `f_owner_id` bigint DEFAULT '0' COMMENT '群账号群主userid',
  `f_remark` varchar(64) DEFAULT NULL COMMENT '备注',
  `f_teaminfo` blob COMMENT '好友分组信息',
  `f_register_time` datetime NOT NULL COMMENT '注册时间',
  `f_update_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  PRIMARY KEY (`f_user_id`),
  UNIQUE KEY `f_username_UNIQUE` (`f_username`),
  KEY `f_user_id` (`f_user_id`),
  KEY `f_id` (`f_id`)
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user`
--

LOCK TABLES `t_user` WRITE;
/*!40000 ALTER TABLE `t_user` DISABLE KEYS */;
INSERT INTO `t_user` VALUES (1,0,'111','huahua','123',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-03 12:34:56','2021-01-13 09:55:25'),(2,1,'222','wsh','222',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-03 20:00:39','2021-01-13 01:48:21'),(5,2,'123','小明','123',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-03 12:30:37','2021-01-13 01:48:21'),(6,3,'1313131313','小红','1313131313',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-10 17:20:04','2021-01-13 01:48:21'),(7,4,'testi','小黑','testi',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-12 09:49:04','2021-01-13 01:48:21'),(10,5,'testj','小黄','testj',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-12 09:58:15','2021-01-13 01:48:21'),(18,6,'333','小紫','333',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-13 01:49:12','2021-01-13 01:48:21'),(19,7,'555','小蓝','555',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-13 02:02:45','2021-01-13 01:48:21'),(20,8,'233','233','张三',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-13 10:09:43','2021-01-13 02:09:43'),(21,9,'1111','name','123',0,NULL,NULL,0,19900101,NULL,NULL,NULL,NULL,0,NULL,NULL,'2021-01-13 17:00:45','2021-01-13 09:00:45');
/*!40000 ALTER TABLE `t_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user_relationship`
--

DROP TABLE IF EXISTS `t_user_relationship`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `t_user_relationship` (
  `f_id` bigint NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `f_user_id1` bigint NOT NULL COMMENT '第一个用户id',
  `f_user_id2` bigint NOT NULL COMMENT '第二个用户id',
  `f_user1_teamname` varchar(32) DEFAULT '我的好友' COMMENT '用户2在用户1的好友分组名称',
  `f_user1_markname` varchar(32) DEFAULT NULL COMMENT '用户2在用户1的备注名称',
  `f_user2_teamname` varchar(32) NOT NULL DEFAULT '我的好友' COMMENT '用户1在用户2的好友分组名称',
  `f_user2_markname` varchar(32) DEFAULT NULL COMMENT '用户1在用户2的备注名称',
  `f_update_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  `f_remark` varchar(64) DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`f_id`),
  KEY `f_id` (`f_id`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user_relationship`
--

LOCK TABLES `t_user_relationship` WRITE;
/*!40000 ALTER TABLE `t_user_relationship` DISABLE KEYS */;
INSERT INTO `t_user_relationship` VALUES (1,0,1,'我的好友',NULL,'我的好友',NULL,'2021-01-12 15:35:43',NULL),(2,0,2,'我的好友',NULL,'我的好友',NULL,'2021-01-12 15:35:43',NULL),(3,0,3,'我的好友',NULL,'我的好友',NULL,'2021-01-12 15:35:56',NULL),(4,0,4,'我的好友',NULL,'我的好友',NULL,'2021-01-12 15:36:09',NULL),(5,0,5,'我的好友',NULL,'我的好友',NULL,'2021-01-12 15:36:09',NULL),(6,1,2,'我的好友',NULL,'我的好友',NULL,'2021-01-12 23:27:30',NULL),(7,0,6,'我的好友',NULL,'我的好友',NULL,'2021-01-12 23:35:35',NULL),(8,6,7,'我的好友',NULL,'我的好友',NULL,'2021-01-12 23:37:59',NULL),(11,0,7,'我的好友',NULL,'我的好友',NULL,'2021-01-13 01:52:04',NULL),(14,-1,8,'我的好友',NULL,'我的好友',NULL,'2021-01-13 03:03:48',NULL),(15,-1,8,'我的好友',NULL,'我的好友',NULL,'2021-01-13 03:04:05',NULL);
/*!40000 ALTER TABLE `t_user_relationship` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-01-13 18:37:38
