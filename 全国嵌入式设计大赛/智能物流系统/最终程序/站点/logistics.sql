-- MySQL dump 10.11
--
-- Host: localhost    Database: logistics
-- ------------------------------------------------------
-- Server version	5.0.67

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `DEPARTURE`
--

DROP TABLE IF EXISTS `DEPARTURE`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `DEPARTURE` (
  `truckid` char(5) NOT NULL,
  `ic` char(20) default NULL,
  `destination` char(20) default NULL,
  PRIMARY KEY  (`truckid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `DEPARTURE`
--

LOCK TABLES `DEPARTURE` WRITE;
/*!40000 ALTER TABLE `DEPARTURE` DISABLE KEYS */;
/*!40000 ALTER TABLE `DEPARTURE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `DILIVERY`
--

DROP TABLE IF EXISTS `DILIVERY`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `DILIVERY` (
  `username` char(20) NOT NULL,
  `truck` char(10) default NULL,
  `departure` char(30) default NULL,
  `destination` char(30) default NULL,
  `description` char(30) default NULL,
  PRIMARY KEY  (`username`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `DILIVERY`
--

LOCK TABLES `DILIVERY` WRITE;
/*!40000 ALTER TABLE `DILIVERY` DISABLE KEYS */;
/*!40000 ALTER TABLE `DILIVERY` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `MERCHANDISE`
--

DROP TABLE IF EXISTS `MERCHANDISE`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `MERCHANDISE` (
  `ic` char(20) NOT NULL,
  `goodsname` char(30) default NULL,
  `quantity` char(5) default NULL,
  `client` char(20) default NULL,
  `destination` char(20) default NULL,
  `rectelnum` char(15) default NULL,
  PRIMARY KEY  (`ic`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `MERCHANDISE`
--

LOCK TABLES `MERCHANDISE` WRITE;
/*!40000 ALTER TABLE `MERCHANDISE` DISABLE KEYS */;
INSERT INTO `MERCHANDISE` VALUES ('325aab55','book','10','syc','rizhao','15006926965'),('5229aa55','arm1138','10','kenan','rizhao','13734306085'),('12ab34cd','s3c2410','12','baoge','rizhao','13734306081');
/*!40000 ALTER TABLE `MERCHANDISE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `REGISTER`
--

DROP TABLE IF EXISTS `REGISTER`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `REGISTER` (
  `uname` char(20) NOT NULL,
  `password` char(45) default NULL,
  `telephone` char(15) default NULL,
  `regdate` char(20) default NULL,
  PRIMARY KEY  (`uname`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `REGISTER`
--

LOCK TABLES `REGISTER` WRITE;
/*!40000 ALTER TABLE `REGISTER` DISABLE KEYS */;
INSERT INTO `REGISTER` VALUES ('liuyubaotaian','e10adc3949ba59abbe56e057f20f883e','15006926965','1304861328'),('aaaa','e10adc3949ba59abbe56e057f20f883e','15006926965','1304920420'),('ssss','e10adc3949ba59abbe56e057f20f883e','15006965123','1304921400'),('dddddd','e10adc3949ba59abbe56e057f20f883e','15006926965','1304960521');
/*!40000 ALTER TABLE `REGISTER` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SDISPATCH1`
--

DROP TABLE IF EXISTS `SDISPATCH1`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `SDISPATCH1` (
  `truckid` char(5) NOT NULL,
  `isidle` char(5) default NULL,
  `destination1` char(20) default NULL,
  `destination2` char(20) default NULL,
  PRIMARY KEY  (`truckid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `SDISPATCH1`
--

LOCK TABLES `SDISPATCH1` WRITE;
/*!40000 ALTER TABLE `SDISPATCH1` DISABLE KEYS */;
/*!40000 ALTER TABLE `SDISPATCH1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SWAREHOUSE1`
--

DROP TABLE IF EXISTS `SWAREHOUSE1`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `SWAREHOUSE1` (
  `ic` char(20) NOT NULL,
  `intime` char(20) default NULL,
  `outtime` char(20) default NULL,
  PRIMARY KEY  (`ic`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `SWAREHOUSE1`
--

LOCK TABLES `SWAREHOUSE1` WRITE;
/*!40000 ALTER TABLE `SWAREHOUSE1` DISABLE KEYS */;
INSERT INTO `SWAREHOUSE1` VALUES ('5229aa55','2011-05-10','2011-05-10'),('325aab55','2011-05-10','2011-05-10'),('95552233','2011-05-10',NULL);
/*!40000 ALTER TABLE `SWAREHOUSE1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SWAREHOUSE2`
--

DROP TABLE IF EXISTS `SWAREHOUSE2`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `SWAREHOUSE2` (
  `ic` char(20) NOT NULL,
  `intime` char(20) default NULL,
  `outtime` char(20) default NULL,
  PRIMARY KEY  (`ic`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `SWAREHOUSE2`
--

LOCK TABLES `SWAREHOUSE2` WRITE;
/*!40000 ALTER TABLE `SWAREHOUSE2` DISABLE KEYS */;
/*!40000 ALTER TABLE `SWAREHOUSE2` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TRUCK0`
--

DROP TABLE IF EXISTS `TRUCK0`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `TRUCK0` (
  `date` char(20) default NULL,
  `time` char(20) default NULL,
  `latitude` char(20) default NULL,
  `lontitude` char(20) default NULL,
  `high` char(10) default NULL,
  `status` char(5) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `TRUCK0`
--

LOCK TABLES `TRUCK0` WRITE;
/*!40000 ALTER TABLE `TRUCK0` DISABLE KEYS */;
INSERT INTO `TRUCK0` VALUES ('1945-10-45','08:45:55','0.0000','0.0000','0.000','V'),('1945-10-45','08:45:55','0.0000','0.0000','0.000','V'),('1945-10-45','08:45:55','0.0000','0.0000','0.000','V'),('1945-10-45','08:45:55','0.0000','0.0000','0.000','V'),('1945-10-45','08:45:55','0.0000','0.0000','0.000','V'),('1945-10-45','08:45:55','0.0000','0.0000','0.000','V'),('1945-10-45','08:45:55','0.0000','0.0000','0.000','V');
/*!40000 ALTER TABLE `TRUCK0` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TRUCK1`
--

DROP TABLE IF EXISTS `TRUCK1`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `TRUCK1` (
  `date` char(20) default NULL,
  `time` char(20) default NULL,
  `latitude` char(20) default NULL,
  `lontitude` char(20) default NULL,
  `high` char(10) default NULL,
  `status` char(5) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `TRUCK1`
--

LOCK TABLES `TRUCK1` WRITE;
/*!40000 ALTER TABLE `TRUCK1` DISABLE KEYS */;
INSERT INTO `TRUCK1` VALUES ('2011-05-11','20:07:55','3526.4869 N','11931.7644 E','-4.0000','A'),('2011-05-11','20:13:57','3526.4876 N','11931.7661 E','-4.0000','A'),('2011-05-11','20:15:00','3526.4874 N','11931.7662 E','-4.0000','A'),('1947--10--44','20:16:05','0.0000 ,','0.0000 ,','0.0000','VATUS'),('2011-05-11','20:17:08','3526.4872 N','11931.7658 E','-4.0000','A'),('2011-05-11','20:17:08','3526.4872 N','11931.7658 E','-4.0000','A'),('2011-05-11','20:17:08','3526.4872 N','11931.7658 E','-4.0000','A'),('2011-05-11','20:17:08','3526.4872 N','11931.7658 E','-4.0000','A'),('1947--10--44','21:29:30','0.0000 ,','0.0000 ,','0.0000','V'),('1947--10--44','21:31:51','0.0000 ,','0.0000 ,','0.0000','V'),('1947--10--44','21:32:55','0.0000 ,','0.0000 ,','0.0000','V'),('1947--10--44','21:33:59','0.0000 ,','0.0000 ,','0.0000','V');
/*!40000 ALTER TABLE `TRUCK1` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-06-03 12:59:09
