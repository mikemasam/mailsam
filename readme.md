-Run in background
  -run in background
  -receive commands
  -manage from remote network

-Read Incoming Mails Async - Done
  -connect to provider and authenticate
  -read new emails
  -compile
  -save to sql
-Send outgoing Mails Async - Done
  -read local emails to be sent
  -connect to provider
  -compile
  -send email
-Read SQL data Async - Done
  -connect to sql
  -read data from sql to object
-Write SQL data Async - Done
  -connect to sql
  -write from object to sql

-Libraries
  -SQL library
  -Run as a service library
  -Email library
  -Flags library

Tasks Ranking
->Deamon
->Linux service flug library
->SQL library
->Mail Library

Main
  -read options and do the needful
Core
  -run terminal
  -run mail handler
