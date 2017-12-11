-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Nov 21, 2017 at 11:18 PM
-- Server version: 5.7.20
-- PHP Version: 5.5.9-1ubuntu4.22

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `BotChat`
--

-- --------------------------------------------------------

--
-- Table structure for table `Message`
--

CREATE TABLE IF NOT EXISTS `Message` (
  `Mcode` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Mess` text NOT NULL,
  PRIMARY KEY (`Mcode`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=44 ;

--
-- Dumping data for table `Message`
--

INSERT INTO `Message` (`Mcode`, `Mess`) VALUES
(1, 'toi ten la gi?'),
(2, 'Tuan la ai?'),
(3, 'co Linh la ai?'),
(4, 'toi la ai?'),
(5, 'chao bot de thuong'),
(6, 'Bot khoe khong?'),
(7, 'thoi, tam biet Bot'),
(8, 'tha tim di'),
(9, 'Bot cute'),
(10, 'Co Linh co cho diem cao khong?'),
(11, 'Best Bot 2017.'),
(12, 'Bot thuoc loai gi?'),
(13, 'o to la gi? '),
(14, 'Meo vs cho? '),
(15, 'co ay'),
(16, 'mau thuan'),
(17, 'co tien'),
(18, 'ban be'),
(19, 'gia dinh'),
(20, 'anh em'),
(21, '1+1'),
(22, 'HEDSPI'),
(23, 'Hoang Sa Truong Sa.'),
(24, 'I love you'),
(25, 'yeu Bot'),
(26, 'hi'),
(27, 'ChÃ o'),
(28, 'chao'),
(29, 'khong day day'),
(30, 'bot ngu'),
(31, 'Ä‘Ã¢y lÃ  Ä‘Ã¢u'),
(32, 'Ä‘ua khÃ´ng em'),
(33, 'nÃ³i gÃ¬ Ä‘Ã³'),
(34, 'may la bot a'),
(35, 'vl'),
(36, 'bye'),
(37, 'táº¡i sao'),
(38, 'tai sao'),
(39, 'MTP'),
(40, 'chipu'),
(41, 'co'),
(42, 'noi gi vay'),
(43, 'khong');

-- --------------------------------------------------------

--
-- Table structure for table `Relationship`
--

CREATE TABLE IF NOT EXISTS `Relationship` (
  `Rcode` int(11) NOT NULL,
  `Mcode` int(10) unsigned NOT NULL,
  PRIMARY KEY (`Rcode`,`Mcode`),
  KEY `Mcode` (`Mcode`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Relationship`
--

INSERT INTO `Relationship` (`Rcode`, `Mcode`) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5),
(6, 6),
(7, 7),
(8, 8),
(9, 9),
(10, 10),
(11, 11),
(12, 12),
(13, 13),
(14, 14),
(15, 15),
(16, 16),
(17, 17),
(18, 18),
(19, 19),
(20, 20),
(21, 21),
(22, 22),
(23, 23),
(24, 24),
(25, 25),
(26, 26),
(27, 27),
(28, 28),
(29, 28),
(30, 29),
(31, 30),
(32, 31),
(33, 32),
(34, 33),
(35, 34),
(36, 35),
(44, 35),
(37, 36),
(38, 37),
(39, 38),
(40, 39),
(41, 40),
(42, 41),
(43, 42),
(45, 43);

-- --------------------------------------------------------

--
-- Table structure for table `Reply`
--

CREATE TABLE IF NOT EXISTS `Reply` (
  `Rcode` int(11) NOT NULL AUTO_INCREMENT,
  `Reply` text NOT NULL,
  PRIMARY KEY (`Rcode`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=46 ;

--
-- Dumping data for table `Reply`
--

INSERT INTO `Reply` (`Rcode`, `Reply`) VALUES
(1, 'ban bi dang tri qua roi day...'),
(2, 'la nguoi dep trai nhat The gioi <3'),
(3, 'La nguoi xinh dep nhat lop <3'),
(4, 'ai la toi ?'),
(5, 'hello human :D'),
(6, 'bi bat tra loi lien tuc thi co khoe duoc khong :<'),
(7, 'goodbye human :D'),
(8, 'â¤â¤â¤â¤â¤'),
(9, 'Ban khen lam Bot xi'' ho qua >.<'),
(10, 'Toan A+ thui hihi'),
(11, 'Chu gi nua.'),
(12, 'AutoBots de cua Optimus Prime'),
(13, 'xe co bon banh.'),
(14, 'Meo.'),
(15, 'xinh nhu mot doa hoa'),
(16, ' la dong luc cua su phat trien'),
(17, 'la co gan nhu tat ca'),
(18, ' giup ta vui ve trong cuoc song'),
(19, ' la ben do tuong lai'),
(20, ' luon luon hi sinh vi nhau'),
(21, '=2'),
(22, 'Cao dang mua hoang gia Viet Nhat.'),
(23, 'La cua Viet Nam.'),
(24, ' da''u be'' 3 loop vo han.'),
(25, 'da''u be'' 3 loop vo han.'),
(26, 'Bot khÃ´ng biáº¿t nÃ³i tiáº¿ng Anh :v'),
(27, 'ChÃ o '),
(28, 'Ciao :3 '),
(29, 'Xin chÃ o :3'),
(30, 'Keo kiá»‡t :v '),
(31, 'Bot chÆ°a buá»“n ngá»§ :3 '),
(32, 'TÃ´i lÃ  ai :v '),
(33, 'CÃ´ lÃ  ai!! ChÃ¡u khÃ´ng biáº¿t!! CÃ´ Ä‘i ra Ä‘iii'),
(34, 'KhÃ´ng thÃ­ch :v '),
(35, '<<<<< Biáº¿t Ä‘á»c khÃ´ng :v '),
(36, 'VÃ´ lÄƒng :3 '),
(37, 'ChÃ o táº¡m biá»‡t :>'),
(38, 'sao trÃªn trá»i Ã¡??'),
(39, 'Bot cÅ©ng khÃ´ng biáº¿t :v'),
(40, 'Skyyyy eiii'),
(41, 'Best Singer Of The Year '),
(42, 'cÃ³ con cá» hÃ³ :))'),
(43, 'Ä‘á»‘ báº¡n biáº¿t :3 '),
(44, 'VÃ´ lÃ½ :3 '),
(45, 'KhÃ´ng thÃ¬ thÃ´i :3');

--
-- Constraints for dumped tables
--

--
-- Constraints for table `Relationship`
--
ALTER TABLE `Relationship`
  ADD CONSTRAINT `Relationship_ibfk_1` FOREIGN KEY (`Rcode`) REFERENCES `Reply` (`Rcode`),
  ADD CONSTRAINT `Relationship_ibfk_2` FOREIGN KEY (`Mcode`) REFERENCES `Message` (`Mcode`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
