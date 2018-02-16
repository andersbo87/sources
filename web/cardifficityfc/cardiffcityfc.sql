--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: tbl_division; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_division (
    divisionid integer NOT NULL,
    divisionname character varying(15) NOT NULL,
    information character varying(1000) NOT NULL
);


ALTER TABLE public.tbl_division OWNER TO andersbo;

--
-- Name: division_id_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE division_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.division_id_seq OWNER TO andersbo;

--
-- Name: division_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: andersbo
--

ALTER SEQUENCE division_id_seq OWNED BY tbl_division.divisionid;


--
-- Name: tbl_nation; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_nation (
    nationid integer NOT NULL,
    nationname character varying(25) NOT NULL
);


ALTER TABLE public.tbl_nation OWNER TO andersbo;

--
-- Name: nation_id_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE nation_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.nation_id_seq OWNER TO andersbo;

--
-- Name: nation_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: andersbo
--

ALTER SEQUENCE nation_id_seq OWNED BY tbl_nation.nationid;


--
-- Name: tbl_player; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_player (
    playerid integer NOT NULL,
    playername character varying(20) NOT NULL,
    playernumber integer NOT NULL,
    positionid integer NOT NULL,
    nationid integer NOT NULL,
    teamid integer NOT NULL
);


ALTER TABLE public.tbl_player OWNER TO andersbo;

--
-- Name: player_id_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE player_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.player_id_seq OWNER TO andersbo;

--
-- Name: player_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: andersbo
--

ALTER SEQUENCE player_id_seq OWNED BY tbl_player.playerid;


--
-- Name: tbl_position; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_position (
    positionid integer NOT NULL,
    positionname character varying(20) NOT NULL,
    positionnotes character varying(100)
);


ALTER TABLE public.tbl_position OWNER TO andersbo;

--
-- Name: position_id_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE position_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.position_id_seq OWNER TO andersbo;

--
-- Name: position_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: andersbo
--

ALTER SEQUENCE position_id_seq OWNED BY tbl_position.positionid;


--
-- Name: tbl_team; Type: TABLE; Schema: public; Owner: andersbo; Tablespace: 
--

CREATE TABLE tbl_team (
    teamid integer NOT NULL,
    teamname character varying(20) NOT NULL,
    teamdescription character varying(100000)
);


ALTER TABLE public.tbl_team OWNER TO andersbo;

--
-- Name: qry_player; Type: VIEW; Schema: public; Owner: andersbo
--

CREATE VIEW qry_player AS
 SELECT tbl_player.playerid,
    tbl_player.playername,
    tbl_player.playernumber,
    tbl_player.positionid,
    tbl_position.positionname,
    tbl_player.nationid,
    tbl_nation.nationname,
    tbl_player.teamid,
    tbl_team.teamname
   FROM tbl_player,
    tbl_position,
    tbl_nation,
    tbl_team
  WHERE (((tbl_position.positionid = tbl_player.positionid) AND (tbl_nation.nationid = tbl_player.nationid)) AND (tbl_team.teamid = tbl_player.teamid));


ALTER TABLE public.qry_player OWNER TO andersbo;

--
-- Name: team_id_seq; Type: SEQUENCE; Schema: public; Owner: andersbo
--

CREATE SEQUENCE team_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.team_id_seq OWNER TO andersbo;

--
-- Name: team_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: andersbo
--

ALTER SEQUENCE team_id_seq OWNED BY tbl_team.teamid;


--
-- Name: divisionid; Type: DEFAULT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY tbl_division ALTER COLUMN divisionid SET DEFAULT nextval('division_id_seq'::regclass);


--
-- Name: nationid; Type: DEFAULT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY tbl_nation ALTER COLUMN nationid SET DEFAULT nextval('nation_id_seq'::regclass);


--
-- Name: playerid; Type: DEFAULT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY tbl_player ALTER COLUMN playerid SET DEFAULT nextval('player_id_seq'::regclass);


--
-- Name: positionid; Type: DEFAULT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY tbl_position ALTER COLUMN positionid SET DEFAULT nextval('position_id_seq'::regclass);


--
-- Name: teamid; Type: DEFAULT; Schema: public; Owner: andersbo
--

ALTER TABLE ONLY tbl_team ALTER COLUMN teamid SET DEFAULT nextval('team_id_seq'::regclass);


--
-- Name: division_id_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('division_id_seq', 1, false);


--
-- Name: nation_id_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('nation_id_seq', 10, true);


--
-- Name: player_id_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('player_id_seq', 29, true);


--
-- Name: position_id_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('position_id_seq', 4, true);


--
-- Data for Name: tbl_division; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_division (divisionid, divisionname, information) FROM stdin;
\.


--
-- Data for Name: tbl_nation; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_nation (nationid, nationname) FROM stdin;
1	Scotland
2	England
3	Brasil
4	Gabon
5	Sør-Afrika
6	Trinidad & Tobago
7	Wales
8	Irland
9	Italia
10	Island
\.


--
-- Data for Name: tbl_player; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_player (playerid, playername, playernumber, positionid, nationid, teamid) FROM stdin;
1	David Marshall	1	1	1	1
2	Lee Peltier	2	2	2	1
3	David da Silva	3	2	3	1
4	Scott Malone	4	2	2	1
5	Bruno Ecuele Manga	5	2	4	1
6	Den Turner	6	2	2	1
7	Peter Whittingham	7	3	2	1
8	Kagisho Dikgacoi	8	3	5	1
9	Kenwyne Jones	9	4	6	1
10	Craig Noone	11	3	2	1
11	Declan John	12	2	7	1
12	Eoin Doyle	13	4	8	1
13	Frederico Macheda	14	4	9	1
14	Conor McAleny	15	4	2	1
15	Matthew Connolly	16	2	2	1
16	Aron Gunnarsson	17	3	10	1
17	Tom Adeyemi	18	3	2	1
18	Anthony Pilkington	19	3	8	1
19	Joe Ralls	21	3	2	1
20	Stuart O Keefe	22	3	2	1
21	Nicky Maynard	23	4	2	1
22	Joe Mason	24	4	8	1
23	Alex Revell	29	4	2	1
24	Matthew Kennedy	30	3	1	1
25	Simon Moore	33	1	2	1
26	Sean Morrison	36	2	2	1
27	Danny Gabbidon	39	2	7	1
29	Ben Wilson	42	1	2	1
28	Kadeem Harris	40	3	2	1
\.


--
-- Data for Name: tbl_position; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_position (positionid, positionname, positionnotes) FROM stdin;
1	Keeper	\N
2	Forsvar	\N
3	Midtbane	\N
4	Spiss	\N
\.


--
-- Data for Name: tbl_team; Type: TABLE DATA; Schema: public; Owner: andersbo
--

COPY tbl_team (teamid, teamname, teamdescription) FROM stdin;
1	A-lag	A-laget er det beste laget Cardiff har å by på. I inneværende sesong spiller de i Sky Bet Championship, det nest øverste nivået i England og Wales.
\.


--
-- Name: team_id_seq; Type: SEQUENCE SET; Schema: public; Owner: andersbo
--

SELECT pg_catalog.setval('team_id_seq', 1, true);


--
-- Name: tbl_division_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_division
    ADD CONSTRAINT tbl_division_pkey PRIMARY KEY (divisionid);


--
-- Name: tbl_nation_nationname_key; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_nation
    ADD CONSTRAINT tbl_nation_nationname_key UNIQUE (nationname);


--
-- Name: tbl_nation_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_nation
    ADD CONSTRAINT tbl_nation_pkey PRIMARY KEY (nationid);


--
-- Name: tbl_player_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_player
    ADD CONSTRAINT tbl_player_pkey PRIMARY KEY (playerid);


--
-- Name: tbl_position_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_position
    ADD CONSTRAINT tbl_position_pkey PRIMARY KEY (positionid);


--
-- Name: tbl_position_positionname_key; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_position
    ADD CONSTRAINT tbl_position_positionname_key UNIQUE (positionname);


--
-- Name: tbl_team_pkey; Type: CONSTRAINT; Schema: public; Owner: andersbo; Tablespace: 
--

ALTER TABLE ONLY tbl_team
    ADD CONSTRAINT tbl_team_pkey PRIMARY KEY (teamid);


--
-- Name: public; Type: ACL; Schema: -; Owner: pgsql
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM pgsql;
GRANT ALL ON SCHEMA public TO pgsql;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

