    INTEGER   MSGCNT, NPOPS, NLUSER, NACOUN, MSGSUP, MSGREC,
     *   MSGKIL, ISBTCH, DBGAIP, MSGVER, MSGRMB, MSGDUM
      CHARACTER MSGTXT*80, TSKNAM*6
      COMMON /MSGCOM/ MSGCNT, NPOPS, NLUSER, NACOUN, MSGSUP, MSGREC,
     *   MSGKIL, ISBTCH, DBGAIP, MSGVER, MSGRMB, MSGDUM
      COMMON /MSGCHR/ MSGTXT, TSKNAM
C                                                          End DMSG.
      INTEGER GET_ONLINE_PTR,NULL_TERM,CREATE_MSGQ,SNDMSGQ,MSG_ID
      INTEGER WRT_SCAN_HDR
      CHARACTER*8 DEST_NAME
      CHARACTER*48 OUTFIL,LOCFIL
      EQUIVALENCE(OUTFIL(1:1),OUTFLL(1))
      CHARACTER*1 CODE(4) /'P','A','B','F'/
      DOUBLE PRECISION RAD_2_H 

      include 'online.inc'

      pointer(ptr,online)
      record  /ONLINE/online
      data ptr/0/
      DATA DEST_NAME/'DASSERV '/

      STRUCTURE /MSGTAG/
      INTEGER TYPE
      CHARACTER*256 BUFF
      END STRUCTURE
 
      RECORD /MSGTAG/ MSG

      POTERR=0
      LEN=-1
      I=NULL_TERM(DEST_NAME)
      IF(MY_CONF_ID.EQ.49) THEN
         WRITE(*,*) ' Master is not encouraged to control the DAS'
         WRITE(*,*) ' Pl come in as user0 for privileged commands'
         WRITE(*,*) ' Command Aborted'
         RETURN
      ENDIF
      PTR=GET_ONLINE_PTR()


      ICOMM = NINT(COMMAND)
      ISUBAR=NINT(XSUBAR)
      IJ=LNBLNK(OUTFIL)
      IPRIV=0
      IF(MY_CONF_ID.EQ.50) IPRIV=1
      MSG.TYPE=4*MY_SUBAR+1
      IF(MY_CONF_ID.GE.65) MSG.TYPE=MSG.TYPE+2


C
C				COMMANDS LESS THAN 10 are for PRIVILEGED
C

      IF(ICOMM.LT.10.AND.IPRIV.NE.1) THEN
         WRITE(*,*)' UNAUTHORISED ISSUING OF PRIVILEGED COMMANDS'
         WRITE(*,*) ' DASCMD  ICOMM=',ICOMM,' COMMAND ABORTED'
         RETURN
      ENDIF

      IF(ICOMM.EQ.1) THEN
C					INITIALISE DAS
         IF(ONLINE.DAS_CNTL.DAS_STATE.NE.0) THEN
            IF(NINT(CPARM(9)).NE.9) THEN
               WRITE(*,*)' DAS INIT FAILED ..ALREADY INITTED' ,
     $         ' ..... SET CPARM(9)=9 TO OVERIDE'
            RETURN
            ENDIF
         ENDIF
C         
C        CMODE=1=>USB  =2=>LSB  =3=>BOTH  =4=>DUMMY 
C
         IF(NINT(CMODE).LT.1.OR.NINT(CMODE).GT.3) THEN
            WRITE(*,*) 'DAS COMMAND FAILED ... INVALID CMODE'
            RETURN
         ENDIF
	     CALL TOLOWER(OUTFIL,IJ)
         ONLINE.DAS_CNTL.CONFIG_FILE=OUTFIL
         I=NULL_TERM(ONLINE.DAS_CNTL.CONFIG_FILE)
         DO I=0,MAX_DAS_SUB-1
            ONLINE.DAS_CNTL.DAS_SUB_STATE(I)=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CMD_NO=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).DAS_SUB_STATE=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.PROJ.ANTMASK=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.PROJ.BANDMASK=15
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.PROJ.CODE=MY_NAME
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.SOURCE.ANTMASK=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.SOURCE.BANDMASK=15
         ENDDO
         I=NINT(TPARM(11))
         TPARM(11)=0
         IF(I.EQ.0)THEN
              I=15
         ENDIF
	     ONLINE.DAS_CNTL.SUB_CNTL(0).CNTL.PROJ.BANDMASK=I
         MSG_ID=CREATE_MSGQ(201)
         IF(MSG_ID.LT.0) THEN
            WRITE(*,*)'DAS INIT FAILED ... CANT OPEN MSGQUE'
            RETURN
         ENDIF
         ONLINE.DAS_CNTL.MSG_ID=I
         CPARM(1)=0
         CALL MKANTMSK(POTERR,I,STR,0)
         CALL GETANTMSK(I,0)
         ONLINE.DAS_CNTL.SUB_CNTL(0).CNTL.PROJ.ANTMASK=I

c		for 2 correlators
         WRITE(MSG.BUFF,"(I2,' 0 das init ',I3,' ',Z8,Z4)")
     $            ,MY_SUBAR,
     $            NINT(CMODE),I,
     $            ONLINE.DAS_CNTL.SUB_CNTL(0).CNTL.PROJ.BANDMASK
c        WRITE(MSG.BUFF,"(I2,' 0 das init ',Z8,Z4)")
c    $            ,MY_SUBAR,
c    $            I,
c    $            ONLINE.DAS_CNTL.SUB_CNTL(0).CNTL.PROJ.BANDMASK
         J=LNBLNK(MSG.BUFF)
c         I=LNBLNK(MY_NAME)-1
c         MSG.BUFF=MY_NAME(:I)//MSG.BUFF(:J)//OUTFIL(:IJ)
         MSG.BUFF=MSG.BUFF(:J)//' '//OUTFIL(:IJ)
         I=NULL_TERM(MSG.BUFF)
         I=SNDMSGQ(MSG_ID,DEST_NAME,MSG)
         IF(I.NE.0) THEN
           WRITE(*,*)'DAS INIT FAILED ... NO ACCEPT, STAT=',I
           RETURN
         ENDIF
         ONLINE.DAS_CNTL.DAS_STATE=1
         ONLINE.DAS_CNTL.SUB_CNTL(I).CMD_NO=1
	     RETURN
      ENDIF

      IF(ICOMM.EQ.2) THEN
C					END DAS SESSION
         IF(ONLINE.DAS_CNTL.DAS_STATE.NE.1) THEN
            IF(NINT(CPARM(9)).NE.9) THEN
               WRITE(*,*)' DAS NOT INITTED ... CMD FAILED',
     $         ' ..... SET CPARM(9)=9 TO OVERIDE'
            RETURN
            ENDIF
         ENDIF
         IF(NINT(CMODE).LT.1.OR.NINT(CMODE).GT.3) THEN
            WRITE(*,*) 'DAS COMMAND FAILED ... INVALID CMODE'
            RETURN
         ENDIF
         I=ONLINE.DAS_CNTL.SUB_CNTL(I).CMD_NO
         WRITE(MSG.BUFF,*),MY_SUBAR,I,' das fini',NINT(CMODE)
c         I=LNBLNK(MY_NAME)
c         MSG.BUFF=MY_NAME(:I)//MSG.BUFF
         I=NULL_TERM(MSG.BUFF)
         I=SNDMSGQ(MSG_ID,DEST_NAME,MSG)
         IF(I.NE.0) THEN
            WRITE(*,*)'DAS FINI FAILED ... NO ACCEPT STAT=',I
            RETURN
         ENDIF
         ONLINE.DAS_CNTL.DAS_STATE=0
         ONLINE.DAS_CNTL.SUB_CNTL(I).CMD_NO=0
         DO I=0,MAX_DAS_SUB-1
            ONLINE.DAS_CNTL.DAS_SUB_STATE(I)=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CMD_NO=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).DAS_SUB_STATE=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.PROJ.ANTMASK=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.PROJ.BANDMASK=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.PROJ.CODE=MY_NAME
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.SOURCE.ANTMASK=0
            ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.SOURCE.BANDMASK=0 
         ENDDO
	     RETURN
      ENDIF
      
      IDAS_SUB=NINT(XSUBAR)
      IF(ICOMM.EQ.3) THEN

C				Start a Project for a subar
         IF(ONLINE.DAS_CNTL.DAS_STATE.NE.1) THEN
            IF(NINT(CPARM(9)).NE.9) THEN
               WRITE(*,*)' DAS NOT INITTED ... CMD FAILED',
     $         ' ..... SET CPARM(9)=9 TO OVERIDE'
            RETURN
            ENDIF
         ENDIF
         I=IDAS_SUB
         IF(ONLINE.DAS_CNTL.DAS_SUB_STATE(I).NE.0) THEN
            IF(NINT(CPARM(9)).NE.9) THEN
            WRITE(*,*)MY_NAME,':  DAS ADD PROJECT  FAILED ',
     $     'PROJECT ',ONLINE.DAS_CNTL.SUB_CNTL(I).CNTL.PROJ.CODE
            WRITE(*,*)' RUNNING.. SET CPA(9)=9 TO OVERIDE'
               RETURN
            ENDIF
         ENDIF
         IF(NINT(CMODE).LT.1.OR.NINT(CMODE).GT.4) THEN
            WRITE(*,*) 'DAS COMMAND FAILED ... INVALID CMODE'
            RETURN
         ENDIF
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.PROJ.CODE=OUTFIL
         I=NULL_TERM(ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.
     $                                       PROJ.CODE)
         CPARM(1)=0
         CALL MKANTMSK(POTERR,I,STR,IDAS_SUB)
         CALL GETANTMSK(I,IDAS_SUB)
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.PROJ.ANTMASK=I
         I=NINT(TPARM(11))
         TPARM(11)=0
         IF(I.EQ.0)THEN
              I=15
         ENDIF
	     ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.PROJ.BANDMASK=I
         I=LNBLNK(MY_NAME)
         LOCFIL="/tmp/proj.hdr."//MY_NAME(:I)
         I=NULL_TERM(LOCFIL)
         I=WRT_SCAN_HDR(LOCFIL,ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL
     $               ,1)
         IF(I.LT.0) THEN
            WRITE(*,*)'UNABLE TO WRITE PROJ HDR, STAT=',I
            RETURN
         ENDIF
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO=1
         WRITE(MSG.BUFF,*),IDAS_SUB,' 1  das addp ',NINT(CMODE),' ',
     $          LOCFIL
         I=NULL_TERM(MSG.BUFF)
         I=SNDMSGQ(MSG_ID,DEST_NAME,MSG)
         IF(I.NE.0) THEN
            WRITE(*,*)'DAS ADDP FAILED ... NO ACCEPT STAT=',I
            RETURN
         ENDIF
         ONLINE.DAS_CNTL.DAS_SUB_STATE(IDAS_SUB)=1
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).DAS_SUB_STATE=0
	     RETURN
      ENDIF


      IF(ICOMM.EQ.4) THEN
C                                       STOP PROJECT
         IF(ONLINE.DAS_CNTL.DAS_STATE.NE.1) THEN
            IF(NINT(CPARM(9)).NE.9) THEN
               WRITE(*,*)' DAS NOT INITTED ... CMD FAILED',
     $         ' ..... SET CPARM(9)=9 TO OVERIDE'
            RETURN
            ENDIF
         ENDIF
         I=IDAS_SUB
         IF(ONLINE.DAS_CNTL.DAS_SUB_STATE(I).NE.1) THEN
          IF(NINT(CPARM(9)).NE.9) THEN
           WRITE(*,*)MY_NAME,':DAS DEL PROJECT  FAILED ',
     $     ' NO PROJECT RUNNING'
           WRITE(*,*)' ..... SET CPARM(9)=9 TO OVERIDE'
           RETURN
          ENDIF
         ENDIF
         I=ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).DAS_SUB_STATE
         IF(I.EQ.1) THEN
            IF(NINT(CPARM(9)).NE.9) THEN
               WRITE(*,*)MY_NAME,':  DAS DEL PROJECT  FAILED ',
     $         ' STOP AQSN FOR THE PROJECT FIRST'
               WRITE(*,*)' ..... SET CPARM(9)=9 TO OVERIDE'
            RETURN
            ENDIF
         ENDIF
         IF(NINT(CMODE).LT.1.OR.NINT(CMODE).GT.3) THEN
            WRITE(*,*) 'DAS COMMAND FAILED ... INVALID CMODE'
            RETURN
         ENDIF
         I=ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO=I+1
         WRITE(MSG.BUFF,*)IDAS_SUB,' ',I,' das delp ',NINT(CMODE)
         I=NULL_TERM(MSG.BUFF)
         I=SNDMSGQ(MSG_ID,DEST_NAME,MSG)
         IF(I.NE.0) THEN
            WRITE(*,*)'DAS STOP FAILED ... NO ACCEPT STAT=',I
            RETURN
         ENDIF
         ONLINE.DAS_CNTL.DAS_SUB_STATE(IDAS_SUB)=0
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).DAS_SUB_STATE=0
         RETURN
      ENDIF



C
C				COMMANDS > THAN 10 are for both MASTER & SUBARRAY controllers
C
      IF(IPRIV.EQ.1)THEN
           IDAS_SUB=NINT(XSUBAR)
      ELSE
           IDAS_SUB=MY_SUBAR
      ENDIF

      IF(ICOMM.EQ.10) THEN
C					INITIALISE a DAS subarray 
         MSG_ID=CREATE_MSGQ(201)
         IF(MSG_ID.LT.0) THEN
            WRITE(*,*)'DAS SUB INIT FAILED ... CANT OPEN MSGQUE'
            RETURN
         ENDIF
         I=ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO=I+1
	 RETURN
      ENDIF

      IF(ICOMM.EQ.11) THEN
C					START SCAN
         IF(ONLINE.DAS_CNTL.DAS_STATE.NE.1) THEN
            IF(NINT(CPARM(9)).NE.9) THEN
               WRITE(*,*)' DAS NOT INITTED ... CMD FAILED',
     $         ' ..... SET CPARM(9)=9 TO OVERIDE'
            RETURN
            ENDIF
         ENDIF
         I=MY_SUBAR
         IF(ONLINE.DAS_CNTL.DAS_SUB_STATE(I).NE.1) THEN
          IF(NINT(CPARM(9)).NE.9) THEN
           WRITE(*,*)MY_NAME,':DAS START SCANFAILED ',
     $     ' NO PROJECT RUNNING'
           WRITE(*,*)' ..... SET CPARM(9)=9 TO OVERIDE'
           RETURN
          ENDIF
         ENDIF
         IF(ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).DAS_SUB_STATE
     $        .NE.0) THEN
          IF(NINT(CPARM(9)).NE.9) THEN
           WRITE(*,*)MY_NAME,':DAS START SCANFAILED ',
     $     ' SCAN ALREADY  RUNNING'
           WRITE(*,*)' ..... SET CPARM(9)=9 TO OVERIDE'
           RETURN
          ENDIF
         ENDIF
         CALL MCOPY(ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).
     $     CNTL.SOURCE.OBJECT,SCOORD,12)
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.RA_APP=
     $                    DCOORD(4)
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.DEC_APP=
     $                    DCOORD(5)
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.RA_DATE=
     $                    DCOORD(6)
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.DEC_DATE=
     $                    DCOORD(7)
C		convert ONLINEs radians/radian to radian/sec of time
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.DRA=
     $                    SCOORD(11)/13750.987083
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.DDEC=
     $                    SCOORD(13)/13750.987083
C		convert reference time in local time (radians) to mjd
         RAD_2_H= 12./3.141592653589793
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.MJD0=
     $         ONLINE.TODAY.MJD+(SCOORD(14)*RAD_2_H-5.5)/24.
         IF(SCOORD(14) .LT. 0.0001) THEN
            ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.MJD0=
     $                    ONLINE.TODAY.MJD
C
C		Comment the above lines and uncomment the lines below if
C		you want to go back to the old dhanishta mode
C
C         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.DRA=
C     $                    SCOORD(11)
C         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.DDEC=
C     $                    SCOORD(13)
C         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.MJD0=
C     $         		   SCOORD(14)
C         IF(SCOORD(14) .LT. 0.0001) THEN
C            ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.MJD0=
C     $                    ONLINE.TODAY.MJD
         ENDIF
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.ANTMASK=
     $          ONLINE.SUBARRAY(MY_SUBAR).PANTMASK          
         I=LNBLNK(MY_NAME)
         LOCFIL="/tmp/scan.hdr."//MY_NAME(:I)
         I=NULL_TERM(LOCFIL)
         I=WRT_SCAN_HDR(LOCFIL,ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL
     $                  ,0)
         IF(I.LT.0) THEN
            WRITE(*,*)'UNABLE TO WRITE SCAN HDR, STAT=',I
            RETURN
         ENDIF
         I=ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO=I+1
         WRITE(MSG.BUFF,*),MY_SUBAR,I,' das start ',LOCFIL
         I=NULL_TERM(MSG.BUFF)
         I=SNDMSGQ(MSG_ID,DEST_NAME,MSG)
         IF(I.NE.0) THEN
            WRITE(*,*)'DAS START FAILED ... NO ACCEPT STAT=',I
            RETURN
         ENDIF
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).DAS_SUB_STATE=1
	 RETURN
      ENDIF

      IF(ICOMM.EQ.12) THEN
C					STOP SCAN
         IF(ONLINE.DAS_CNTL.DAS_STATE.NE.1) THEN
            IF(NINT(CPARM(9)).NE.9) THEN
               WRITE(*,*)' DAS NOT INITTED ... CMD FAILED',
     $         ' ..... SET CPARM(9)=9 TO OVERIDE'
            RETURN
            ENDIF
         ENDIF
         I=MY_SUBAR
         IF(ONLINE.DAS_CNTL.DAS_SUB_STATE(I).NE.1) THEN
          IF(NINT(CPARM(9)).NE.9) THEN
           WRITE(*,*)MY_NAME,':DAS STOP SCAN FAILED ',
     $     ' NO PROJECT RUNNING'
           WRITE(*,*)' ..... SET CPARM(9)=9 TO OVERIDE'
           RETURN
          ENDIF
         ENDIF
         IF(ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).DAS_SUB_STATE
     $        .NE.1) THEN
          IF(NINT(CPARM(9)).NE.9) THEN
           WRITE(*,*)MY_NAME,':DAS START SCANFAILED ',
     $     ' SCAN NOT  RUNNING'
           WRITE(*,*)' ..... SET CPARM(9)=9 TO OVERIDE'
           RETURN
          ENDIF
         ENDIF
         I=ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO=I+1
         WRITE(MSG.BUFF,*),MY_SUBAR,' ',I,' das stop '
         I=NULL_TERM(MSG.BUFF)
         I=SNDMSGQ(MSG_ID,DEST_NAME,MSG)
         IF(I.NE.0) THEN
            WRITE(*,*)'DAS STOP FAILED ... NO ACCEPT STAT=',I
            RETURN
         ENDIF
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).DAS_SUB_STATE=0
         RETURN
      ENDIF

      IF(ICOMM.EQ.13) THEN
C					ARBITRARY STRING
         I=ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CMD_NO=I+1
         WRITE(MSG.BUFF,*)MY_SUBAR,I,OUTFIL
         I=NULL_TERM(MSG.BUFF)
         I=SNDMSGQ(MSG_ID,DEST_NAME,MSG)
         IF(I.NE.0) THEN
            WRITE(*,*)'DAS CMDSTR FAILED ... NO ACCEPT STAT=',I
            RETURN
         ENDIF
         RETURN

      ENDIF


C
C				COMMANDS > THAN 20 are for both MASTER & SUBARRAY controllers
C				mainly meant for putting in info in the DAS structure
C

      IF(ICOMM.EQ.21) THEN
C					fill project name
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.PROJ.TITLE=OUTFIL
         I=NULL_TERM(ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.
     $                                       PROJ.TITLE)
	 RETURN
      ENDIF

      IF(ICOMM.EQ.22) THEN
C					fill observer info
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.PROJ.OBSERVER=OUTFIL
         I=NULL_TERM(ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.PROJ.
     $                         OBSERVER)
	 RETURN
      ENDIF


      IF(ICOMM.EQ.24) THEN
C					fill freq and source structures
         DO I=1,10
	    LO(I)=TPARM(I)*1000000.
	 ENDDO

         CALL MCOPY(ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.FREQ,
     $                   LO,80)
         I=NINT(TPARM(11))
         IF(I.EQ.0) 
     $      I=ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.PROJ.BANDMASK
	 ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.BANDMASK=I
	 RETURN
      ENDIF

      IF(ICOMM.EQ.26) THEN
c					fill source codes
         J=0
         DO I=1,4
         IF(INDEX(OUTFIL,CODE(I)).GT.0) J=J+2**(I-1)
         ENDDO
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.QUAL=J
         IF(J.GT.0) J=1
         ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.CALCODE=J
         write (*,*) 'SOURCE CODES=',J,
     $      ONLINE.DAS_CNTL.SUB_CNTL(IDAS_SUB).CNTL.SOURCE.QUAL
      RETURN
      ENDIF


      STR(1:)="UNRECOGNISED DAS CONTROLLER COMMAND"
      WRITE(MSGTXT,*) "UNRECOGNISED DAS CONTROLLER COMMAND"

      RETURN
      END

