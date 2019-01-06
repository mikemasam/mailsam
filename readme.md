-Deamon
  -run as a linux service
  -read flugs from linux service manager
-Read Incoming Mails Async
  -connect to provider and authenticate
  -read new emails
  -compile
  -save to sql
-Send outgoing Mails Async
  -read local emails to be sent
  -connect to provider
  -compile
  -send email
-Read SQL data Async
  -connect to sql
  -read data from sql to object
-Write SQL data Async
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



