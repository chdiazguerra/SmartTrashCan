-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 28-06-2023 a las 07:26:22
-- Versión del servidor: 10.4.19-MariaDB
-- Versión de PHP: 8.0.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "-04:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `basura`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `basureros`
--

CREATE TABLE `basureros` (
  `num` int(11) NOT NULL,
  `id` varchar(15) NOT NULL,
  `lat` varchar(10) NOT NULL,
  `lon` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `basureros`
--

INSERT INTO `basureros` (`num`, `id`, `lat`, `lon`) VALUES
(3, '55c326d573854e6', '-33.45753', '-70.66317'),
(4, '6f20b65f89d4ccd', '-33.45802', '-70.66171'),
(1, 'de2be685418180f', '-33.45780', '-70.66239'),
(2, 'edb2e379983c5be', '-33.45788', '-70.66243');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `basureros`
--
ALTER TABLE `basureros`
  ADD PRIMARY KEY (`id`),
  ADD KEY `num` (`num`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `basureros`
--
ALTER TABLE `basureros`
  MODIFY `num` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
