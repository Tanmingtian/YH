/*
*********************************************************************************************************
*	                                  
*	Ä£¿éÃû³Æ : È«Æ´ÒôÊäÈë·¨
*	ÎÄ¼şÃû³Æ : MainTask.c
*	°æ    ±¾ : V1.0
*	Ëµ    Ã÷ : Õâ²¿·Öºº×Ö±íºÍ¼ìË÷º¯ÊıÀ´×ÔÍøÂç£¬Ê¹ÓÃ±¾¹¤³ÌÇë±£Ö¤´ËÎÄ¼şµÄÊôĞÔÊÇUTF-8¸ñÊ½.
*                                     
*	ĞŞ¸Ä¼ÇÂ¼ :
*		°æ±¾ºÅ    ÈÕÆÚ          ×÷Õß          ËµÃ÷
*		v1.0    2014-07-07    Eric2013        Ê×·¢
*	
*	Copyright (C), 2014-2015, °²¸»À³µç×Ó www.armfly.com
*
*********************************************************************************************************
*/
#include "pysearch.h"
#include "string.h"


/*
*********************************************************************************************************
*	                         ºº×ÖÁĞ±í
*********************************************************************************************************
*/
const unsigned char PY_mb_space []={""};
const unsigned char PY_mb_a     []={"°¡°¢ºÇß¹àÄëçï¹"}; 
const unsigned char PY_mb_ai    []={"°®°«°¤°¥°­°©°¬°¦°§°ª°¯°£°¨´ôàÉæÈè¨êÓŞßíÁàÈïÍö°"};
const unsigned char PY_mb_an    []={"°´°²°µ°¶°³°¸°°°±°·³§¹ãâÖŞîáíï§èñÚÏğÆÛû÷ö"};
const unsigned char PY_mb_ang   []={"°º°¹°»Ñö"};
const unsigned char PY_mb_ao    []={"°À°¼°Á°Â°¾°Ã°½°¿°ÄÏùŞÖæÁâÚæñà»ÛêåÛñúòüéáöË÷¡÷é"};
const unsigned char PY_mb_ba    []={"°Ñ°Ë°É°Ö°Î°Õ°Ï°Í°Å°Ç°Ó°Ô°È°Ğ°Ê°Ì°Ò°ÆôÎÜØá±öÑîÙ÷É"};
const unsigned char PY_mb_bai   []={"°Ù°×°Ú°Ü°Ø°İ°Û²®°ŞŞãßÂêş"};
const unsigned char PY_mb_ban   []={"°ë°ì°à°ã°è°á°æ°ß°å°é°â°ç°ê°ä°íñ­ÛàîÓô²Úæ"};
const unsigned char PY_mb_bang  []={"°ï°ô°ó°õ°÷°î°ñ°ö°ø°ğ°ò°ùäºİò"};
const unsigned char PY_mb_bao   []={"°ü±§±¨±¥±£±©±¡±¦±¬°ş±ªÅÙ±¢°ı±¤°ú°û±«ÅÚÆÙöµæßìÒñÙğ±õÀİá"};
const unsigned char PY_mb_bei   []={"±»±±±¶±­±³±¯±¸±®±°±´±²±µ±º±·±¹±ÛñØã£İíğÇöÍßÂ"};
const unsigned char PY_mb_ben   []={"±¾±¼±½±¿º»ï¼êÚÛÎÛĞ"};
const unsigned char PY_mb_beng  []={"±Ä±Á±Â±À±Å°ö±Ãê´àÔ"};
const unsigned char PY_mb_bi    []={"±È±Ê±Õ±Ç±Ì±Ø±Ü±Æ±Ï±Û±Ë±É±Ú±Í±Ò±×±Ù±Î±Ğ±Ó±Ö±İ±Ñ±ÔÃØÃÚïõŞµİ©ÜÅİÉØ°ñÔî¯ÙÂæÔáùóÙóëó÷ô°ÜêôÅâØîéõÏßÁã¹êÚääå¨èµßÙ÷Âåöåşæ¾"};
const unsigned char PY_mb_bian  []={"±ß±ä±ã±é±à±ç±â±á±Ş±å±æ±èâíí¾ØÒãêíÜòùñÛöıóÖÜĞñ¹ÛÍçÂ"};
const unsigned char PY_mb_biao  []={"±í±ê±ë±ìè¼æ»ì©ì­÷§ñ¦ì®ïğñÑæôïÚ"};
const unsigned char PY_mb_bie   []={"±ğ±ï±î±ñõ¿"};
const unsigned char PY_mb_bin   []={"±ö±ô±÷±ò±ó±õáÙë÷éëçÍ÷ÆÙÏéÄ÷ŞïÙçã"};
const unsigned char PY_mb_bing  []={"²¢²¡±ø±ù±û±ıÆÁ±ü±ú±şŞğéÄÙ÷Úû"};
const unsigned char PY_mb_bo    []={"²¦²¨²¥²´²©²®²µ²£°ş±¡²ª²¤²§²«²±²¯°ã°Ø²°²³²¬²­²²ÆÇ²·íçõËéŞÙñğ¾õÛà£Ş¬ô¤îàâÄë¢"};
const unsigned char PY_mb_bu    []={"²»²½²¹²¼²¿²¶²·²¾²¸±¤²º²ÀÆÒê³åÍêÎîßîĞõ³ß²"};
const unsigned char PY_mb_ca    []={"²Á²ğíåàê"};
const unsigned char PY_mb_cai   []={"²Â²Å²Ä²Æ²Ã²É²Ê²Ç²È²Ë²Ì"};
const unsigned char PY_mb_can   []={"²Ï²Ğ²ô²Î²Ò²Ñ²Í²Óæîè²åî÷õôÓ"};
const unsigned char PY_mb_cang  []={"²Ø²Ö²×²Õ²ÔØ÷"};
const unsigned char PY_mb_cao   []={"²İ²Ù²Ü²Û²ÚàĞô½ó©äî"};
const unsigned char PY_mb_ce    []={"²á²à²ß²â²Şâü"};
const unsigned char PY_mb_cen   []={"²Îá¯ä¹"};
const unsigned char PY_mb_ceng  []={"Ôø²ã²äàá"};
const unsigned char PY_mb_cha   []={"²é²å²æ²è²î²í²ë²ì²ç²êÉ²²ïé«é¶ïïñÃãââÇéßæ±è¾ïÊàê"};
const unsigned char PY_mb_chai  []={"²Ë²ñ²ğ²î²òîÎğûò²Ù­"};
const unsigned char PY_mb_chan  []={"²ú²ø²ô²ó²û²ü²ù²÷²õµ¥²öêèæ¿İÛÚÆÙæâÜåîó¸åñïââãäıìøæöõğå¤"};
const unsigned char PY_mb_chang []={"³¤³ª³£³¡³§³¢³¦³©²ı³¨³«³¥²şÉÑöğë©İÅã®æÏáäÛËãÑâêØöêÆÜÉæ½"};
const unsigned char PY_mb_chao  []={"³¯³­³¬³³³±³²³´³°½Ë´Â³®â÷ìÌñéêË"};
const unsigned char PY_mb_che   []={"³µ³·³¶³¸³¹³ß³ºÛåíº"};
const unsigned char PY_mb_chen  []={"³Ã³Æ³½³¼³¾³¿³Á³Â³Ä³È³À³»é´ŞÓÚÈí×Úßå·ö³àÁØ÷è¡"};
const unsigned char PY_mb_cheng []={"³É³ËÊ¢³Å³Æ³Ç³Ì³Ê³Ï³Í³Ñ³Ò³Î³È³ĞëóèßÛôîñàáîõõ¨êÉñÎèÇòÉØ©îª"};
const unsigned char PY_mb_chi   []={"³Ô³ß³Ù³Ø³á³Õ³à³İ³Ü³Ö³â³Ş³Ú³Û³ã³×õØÛæÜİÜ¯âÁæÊôùñİë·ßêñ¡ò¿à´ğ·í÷ó¤óø÷Îß³áÜó×àÍ"};
const unsigned char PY_mb_chong []={"³åÖØ³æ³ä³è³çÓ¿ÖÖô¾âçô©ï¥ã¿Üû"};
const unsigned char PY_mb_chou  []={"³é³î³ô³ğ³ó³í³ñ³ê³ï³ì³ë³òã°Ù±àüñ¬öÅ"};
const unsigned char PY_mb_chu   []={"³ö´¦³õ³ú³ı´¥³÷³ş´¡´¢Ğó³ü´£´¤³ù³ø³ûèúèÆÛ»âğç©Ø¡ãÀõé÷íòÜéË"};
const unsigned char PY_mb_chuai []={"´§ëúà¨àÜŞõõß"};
const unsigned char PY_mb_chuan []={"´©´¬´«´®´¨´­´ªë°å×îËô­â¶çİ"};
const unsigned char PY_mb_chuang[]={"´°´²´³´´´¯´±âë"};
const unsigned char PY_mb_chui  []={"´µ´¹´¶´¸´·×µé³é¢Úï"};
const unsigned char PY_mb_chun  []={"´º´½´¿´À´¼´¾´»òíİ»ğÈ"};
const unsigned char PY_mb_chuo  []={"´Á´ÂõÖà¨öºê¡"};
const unsigned char PY_mb_ci    []={"´Î´Ë´Ê´É´È´Æ´Å´Ç´Ì´ÄËÅ´Ã´Í²î×ÈßÚğËìôôÙ"};
const unsigned char PY_mb_cong  []={"´Ó´Ô´Ğ´Ò´Ï´ÑçıèÈäÈè®æõÜÊ"};
const unsigned char PY_mb_cou   []={"´Õé¨ê£ëí"};
const unsigned char PY_mb_cu    []={"´Ö´×´Ø´Ù×äáŞâ§İıõ¾õ¡éãõí"};
const unsigned char PY_mb_cuan  []={"´Ü´Ú´ÛÔÜß¥Ùàìàïé"};
const unsigned char PY_mb_cui   []={"´ß´à´İ´ä´Ş´ãË¥´á´âè­ßıã²İÍë¥éÁ"};
const unsigned char PY_mb_cun   []={"´å´ç´æ¶×ââñå"};
const unsigned char PY_mb_cuo   []={"´í´é´ê´ì´ë´èáÏØÈõºëâğîõãğûï±ïó"};
const unsigned char PY_mb_da    []={"´ó´ğ´ï´ò´î´ñËşóÎŞÇßÕñ×ğãâò÷°æ§í³àª÷²"};
const unsigned char PY_mb_dai   []={"´ø´ú´ô´÷´ı´ü´ş´õ´ûµ¡´ö´ó´ùß¾çéåÊá·ß°÷ìææçªÜ¤"};
const unsigned char PY_mb_dan   []={"µ«µ¥µ°µ£µ¯µ§µ¨µ­µ¤µ¢µ©µªµ®µ¦µ¬Ê¯ğãå£ğ÷İÌééíññõóìêæÙÙà¢"};
const unsigned char PY_mb_dang  []={"µ±µ³µ²µµµ´ÚÔîõå´İĞÛÊñÉí¸"};
const unsigned char PY_mb_dao   []={"µ½µÀµ¹µ¶µºµÁµ¾µ·µ¿µ¼µ¸µ»àüôîâáìâë®ß¶"};
const unsigned char PY_mb_de    []={"µÄµØµÃµÂµ×ï½"};
const unsigned char PY_mb_deng  []={"µÈµÆµËµÇ³ÎµÉµÊµÅíãïëàâáØê­ô£"};
const unsigned char PY_mb_di    []={"µØµÚµ×µÍµĞµÖµÎµÛµİµÕµÜµŞµÌµÄµÓÌáµÑµÏµÒµÔµÙêëÛ¡ÚĞÚ®àÖèÜ÷¾ôÆØµé¦íûæ·İ¶íÚïáÛæÙáíÆ"};
const unsigned char PY_mb_dia	[]={"àÇ"};
const unsigned char PY_mb_dian  []={"µãµçµêµîµíµàµßµæµâµëµìµäµèµåµáµéõÚîäÛãÚçñ²ô¡çèáÛñ°"};
const unsigned char PY_mb_diao  []={"µôµöµğµõµñµ÷µóµïµòÄñîöï¢öôõõ"};
const unsigned char PY_mb_die   []={"µùµøµşµúµûµüµıëºÜ¦ğ¬ŞéõŞñóöøÛìà©"};
const unsigned char PY_mb_ding  []={"¶¥¶¨¶¢¶©¶£¶¡¶¤¶¦¶§î®çàîúëëíÖğÛØêñôôúà¤"};
const unsigned char PY_mb_diu   []={"¶ªîû"};
const unsigned char PY_mb_dong  []={"¶¯¶«¶®¶´¶³¶¬¶­¶°¶±¶²á¼ğ´ÛíëËëØíÏë±á´ßË"};
const unsigned char PY_mb_dou   []={"¶¼¶·¶¹¶º¶¸¶¶¶»¶µ¶Áò½ñ¼óûİú"};
const unsigned char PY_mb_du    []={"¶Á¶È¶¾¶É¶Â¶À¶Ç¶Æ¶Ä¶Ã¶Å¶½¶¼¶¿¶Ê¶Ùó¼óÆà½äÂèüë¹÷ò÷ÇÜ¶"};
const unsigned char PY_mb_duan  []={"¶Î¶Ì¶Ï¶Ë¶Í¶Ğé²ìÑóı"};
const unsigned char PY_mb_dui   []={"¶Ô¶Ó¶Ñ¶Ò¶ØïæíÔí¡í­"};
const unsigned char PY_mb_dun   []={"¶Ö¶Ù¶×¶Õ¶Ø¶Û¶Ü¶Ú¶İ²»õ»ãçíïïæíâìÀí»"};
const unsigned char PY_mb_duo   []={"¶à¶ä¶á¶æ¶ç¶â¶å¶è¶é¶Ş¶ßÍÔ¶È¶ãõâãõßÍîìñÖßáç¶"};
const unsigned char PY_mb_e     []={"¶öÅ¶¶î¶ì¶ê¶ó¶í¶ï°¢¶ô¶ë¶ğ¶ñ¶ò¶õï°ÚÌÛÑïÉãÕİàÜÃéîæ¹İ­öùò¦ëñãµßÀØ¬ğÊåí"};
const unsigned char PY_mb_en    []={"¶÷ŞôàÅ"};
const unsigned char PY_mb_er    []={"¶ø¶ş¶ú¶ù¶ü¶û·¡¶ıçíöÜğ¹Ù¦åÇîï"};
const unsigned char PY_mb_fa    []={"·¢·¨·£·¥·¦·¤·§·©ÛÒíÀ"};
const unsigned char PY_mb_fan   []={"·´·¹·­·¬·¸·²·«·µ·º·±·³···¶·®·ª·¯·°ìÜŞÀî²Ş¬õìèóá¦"};
const unsigned char PY_mb_fang  []={"·Å·¿·À·Ä·¼·½·Ã·Â·»·Á·¾îÕáİÚúèÊô³öĞ"};
const unsigned char PY_mb_fei   []={"·Ç·É·Ê·Ñ·Î·Ï·Ë·Í·Ğ·Æ·Ì·Èóõòãëèìéåúì³áôÜÀã­ïĞö­ôäé¼äÇöîç³ğò"};
const unsigned char PY_mb_fen   []={"·Ö·İ·Ò·Û·Ø·Ü·ß·×·Ş·à·Ó·Ù·Ô·Õ·Úèûå¯ö÷çãÙÇ÷÷"};
const unsigned char PY_mb_feng  []={"·ç·â·ê·ì·ä·á·ã·è·ë·î·í·ï·å·æ·éí¿ÙºÛºİ×ããßô"};
const unsigned char PY_mb_fo    []={"·ğ"};
const unsigned char PY_mb_fou   []={"·ñó¾"};
const unsigned char PY_mb_fu    []={"¸±·ù·ö¸¡¸»¸£¸º·ü¸¶¸´·ş¸½¸©¸«¸°¸¿·÷·ò¸¸·û·õ·ó¸³¸¨¸®¸¯¸¹¸¾¸§¸²·ø·ô·ú·ğ·ı¸µ¸¼¸¥¸¢¸¤ÊĞ¸¦¸ª¸¬¸­¸·¸ÀíëíÉÜŞõÃõÆò¶ÜÀöÖá¥ÜòäæòİŞÔİÊòğöûòóç¦ç¨êçî·ïûÙëôïÙìèõİ³æÚğ¥æââöìğß»Û®Ü½åõ"};
const unsigned char PY_mb_ga    []={"¸Á¸ì¼Ğ¸Â¿§ÔşîÅÙ¤ê¸ŞÎæØæÙßÈ"};
const unsigned char PY_mb_gai   []={"¸Ã¸Ä¸Ç¸Å¸Æ½æ¸Èê®ÛòØ¤Úëêà"};
const unsigned char PY_mb_gan   []={"¸Ï¸É¸Ğ¸Ò¸Í¸Ê¸Î¸Ì¸Ë¸Ó¸Ñêºôûí·ğáãïÜÕß¦ç¤éÏä÷äÆŞÏÛá"};
const unsigned char PY_mb_gang  []={"¸Õ¸Ö¸Ù¸Û¸×¸Ú¸Ü¸Ô¸Ø¿¸óàî¸í°"};
const unsigned char PY_mb_gao   []={"¸ß¸ã¸æ¸å¸à¸İ¸á¸â¸ä¸ŞÛ¬Ú¾ê½çÉØºéÀï¯éÂŞ»"};
const unsigned char PY_mb_ge    []={"¸ö¸÷¸è¸î¸ç¸é¸ñ¸ó¸ô¸ï¿©¸ì¸ğ¸ò¸ê¸ë¸í¸ÇÒÙºÏ¸õíÑ÷Àò¢ñËÜªò´ÛÙïÓØîô´ØªàÃëõë¡æüÛÁ"};
const unsigned char PY_mb_gei   []={"¸ø"};
const unsigned char PY_mb_gen   []={"¸ú¸ùßçİ¢Ø¨ôŞ"};
const unsigned char PY_mb_geng  []={"¸ü¸û¾±¹£¹¢¸ı¸ş¹¡âÙöáßìç®"};
const unsigned char PY_mb_gong  []={"¹¤¹«¹¦¹²¹­¹¥¹¬¹©¹§¹°¹±¹ª¹®¹¯¹¨ºìëÅö¡çîò¼"};
const unsigned char PY_mb_gou   []={"¹»¹µ¹·¹³¹´¹º¹¹¹¶¹¸¾äá¸ì°èÛ÷¸êíçÃóÑÚ¸åÜæÅóôØş"};
const unsigned char PY_mb_gu    []={"¹Å¹É¹Ä¹È¹Ê¹Â¹¿¹Ã¹Ë¹Ì¹Í¹À¹¾¹Ç¹¼¹Á¹Æ¼Ö¹½èôğ³ãééïáÄİÔğÀ÷½îÜëûôşßÉöñÚ¬êôî­ì±ïÀêöğóõıòÁî¹ØÅ"};
const unsigned char PY_mb_gua   []={"¹Ò¹Î¹Ï¹Ñ¹Ğ¹ÓØÔßÉëÒğ»èéÚ´"};
const unsigned char PY_mb_guai  []={"¹Ö¹Õ¹ÔŞâ"};
const unsigned char PY_mb_guan  []={"¹Ø¹Ü¹Ù¹Û¹İ¹ß¹Ş¹à¹Ú¹á¹×ÂÚîÂñæİ¸ŞèäÊ÷¤ğÙÙÄ"};
const unsigned char PY_mb_guang []={"¹â¹ã¹äèæáîßÛë×"};
const unsigned char PY_mb_gui   []={"¹é¹ó¹í¹ò¹ì¹æ¹è¹ğ¹ñ¹ê¹î¹ë¹å¹ç¹ô¿ş¹ïÈ²âÑå³èíØÛ÷¬öÙğ§ØĞæ£êĞóşêÁ"};
const unsigned char PY_mb_gun   []={"¹ö¹÷¹õöçÙòíŞçµ"};
const unsigned char PY_mb_guo   []={"¹ı¹ú¹û¹ü¹ø¹ùÎĞÛöé¤ñøÙåâ£áÆŞâàşßÃë½òäòå"};
const unsigned char PY_mb_ha    []={"¹ş¸òÏºîş"};
const unsigned char PY_mb_hai   []={"»¹º£º¦¿Èº¤º¢º§º¡º¥àËõ°ëÜ"};
const unsigned char PY_mb_han   []={"º°º¬º¹º®ºººµº¨º«º¸º­º¯º©º²º±º³º´º¶º·ºªÚõİÕŞşå«ãÛñüòÀìÊò¥êÏ÷ı"};
const unsigned char PY_mb_hang  []={"ĞĞÏïº½º»º¼¿Ôñşãìç¬çñ"};
const unsigned char PY_mb_hao   []={"ºÃºÅºÆº¿º¾ºÂºÁºÀºÄºÑ¸äê»ò«å°àãòºàÆğ©İïå©Ş¶"};
const unsigned char PY_mb_he    []={"ºÍºÈºÏºÓºÌºËºÎºÇºÉºØºÕºÖºĞº×ºÊºÑºÒºÔÏÅàÀÛÀîÁôçãØò¢ÛÖÚ­æüêÂ"};
const unsigned char PY_mb_hei   []={"ºÚºÙ"};
const unsigned char PY_mb_hen   []={"ºÜºİºŞºÛ"};
const unsigned char PY_mb_heng  []={"ºáºãºßºâºàĞĞèìçñŞ¿"};
const unsigned char PY_mb_hong  []={"ºìºäºåºçºéºêºæºèºëÚ§ÙêŞ®ãÈŞ°Ùäİ¦ãü"};
const unsigned char PY_mb_hou   []={"ºóºñºğºíºîºòºïö×óóÜ©ááåËô×÷¿ğú"};
const unsigned char PY_mb_hu    []={"ºş»§ºô»¢ºø»¥ºú»¤ºı»¡ºöºüºûºù»¦ºõÏ·ºËºÍº÷»£ğÉÙüâïğ×óËìæìè÷½ä°ìïõ­çúàñìÃéõğ­ìÎõúğÀâ©ã±á²äïì²ßüéÎ"};
const unsigned char PY_mb_hua   []={"»°»¨»¯»­»ª»®»¬»©»«»íîüèëæèí¹"};
const unsigned char PY_mb_huai  []={"»µ»³»´»±»²»®õ×"};
const unsigned char PY_mb_huan  []={"»»»¹»½»·»¼»º»¶»Ã»Â»Á»À»¿»¸»¾äñâµß§åÕöéÛ¨÷ßå¾Û¼ïÌà÷ä¡İÈçÙä½"};
const unsigned char PY_mb_huang []={"»Æ»Å»Î»Ä»É»Ë»Ê»Ñ»Ì»È»Ç»Ğ»Í»ÏÚòëÁäêóòáåöü"};
const unsigned char PY_mb_hui   []={"»Ø»á»Ò»æ»Ó»ã»Ô»Ù»Ú»İ»Ş»Õ»Ö»à»Û»ß»×»ä»²»Ü»â»ååçä«çõŞ¥à¹í£ßÜêÍãÄ÷âÚ¶ó³Üîä§ßÔò³ÜöçÀ"};
const unsigned char PY_mb_hun   []={"»ì»è»ç»ë»é»êãÔçõâÆäãÚ»"};
const unsigned char PY_mb_huo   []={"»ò»î»ğ»ï»õºÍ»ñ»ö»í»ô»óàëïìñëØåŞ½ß«ïÁó¶îØâ·"};
const unsigned char PY_mb_ji    []={"¼¸¼°¼±¼È¼´»ú¼¦»ı¼Ç¼¶¼«¼Æ¼·¼º¼¾¼Ä¼ÍÏµ»ù¼¤¼ª¼¹¼Ê»÷»ø»û»ş¼¡¼¢¼£¼¥¼§¼¨¼¬¼­¼®¼©¼¯¼²¼³¼µ¼»¼¼¼½¼¿¼À¼Á¼Â¼Ã¼ÅÆÚÆäÆæ¼ÉÆë¼Ë¼Ì¸ø¸ï»üÛÔä©öİåìì´êªöêïúí¶ğ¢ê«ò±ÚµóÅôßóÇØŞß´İğõÒáÕŞáõÕö«ßóçÜÜùñ¤çáî¿Ø¢ÙÊÜ¸Ù¥êåé®÷ÙßÒŞªêé÷ä"};
const unsigned char PY_mb_jia   []={"¼Ò¼Ó¼Ù¼Û¼Ü¼×¼Ñ¼Ğ¼Î¼İ¼Ş¼Ï¼Ô¼Õ¼Ø¼ÚÇÑ¼ÖîòİçåÈê©ä¤ïØğèí¢áµõÊØÅÙ¤ëÎóÕçìğıÛ£ôÂòÌ"};
const unsigned char PY_mb_jian  []={"¼û¼ş¼õ¼â¼ä¼ü¼ú¼ç¼æ½¨¼ì¼ı¼å¼ò¼ô¼ß¼à¼á¼é½¡¼è¼ö½£½¥½¦½§¼øÇ³¼ù¼ñ¼í¼ã¼ó¼î¼ï¼ğ½¢¼÷¼ê¼ë½¤ôå÷µê§ÚÉêğèÅëìõÂçÌŞöê¯ë¦İÑöäóÈÚÙé¥àîå¿ñĞõİíúåÀğÏİóÙÔïµäÕ"};
const unsigned char PY_mb_jiang []={"½«½²½­½±½µ½¬½©½ª½´½¯½®½³Ç¿½°ºçôøíäçÖêññğç­Üüôİä®"};
const unsigned char PY_mb_jiao  []={"½Ğ½Å½»½Ç½Ì½Ï½É¾õ½¹½º½¿½ÊĞ£½Á½¾½Æ½½½Ã½¼½À½¶½Î½Ñ½·½¸½È½Â½Í½Ä½ËáèÜ´ÙÕòÔë¸á½õÓæ¯ğ¨ÜúğÔàİõ´Ù®äĞöŞŞØ"};
const unsigned char PY_mb_jie   []={"½Ó½Ú½Ö½è½Ô½Ø½â½ç½á½ì½ã½Ò½ä½é½×½Ù½æ½ß½à½ê½å¼Û¿¬½Õ½Û½Ü½İ½ë½Ş¼ÒÙÊèîà®Ş×÷ºôÉò»àµò¡öÚæ¼íÙÚ¦æİğÜÚµ"};
const unsigned char PY_mb_jin   []={"½ø½ü½ñ½ö½ô½ğ½ï¾¡¾¢½û½ş½õ½ú½î½ò½÷½í½ó½ı½ùâÛèªâËéÈñÆİÀİ£ñæàäçÆÚáæ¡êáêî"};
const unsigned char PY_mb_jing  []={"¾¹¾²¾®¾ª¾­¾µ¾©¾»¾´¾«¾°¾¯¾º¾³¾¶¾£¾§¾¨¾¬¾±¾¤¾¥¾¦¾¢¾·¾¸ëÂâ°ÚåëæåòØÙã½æºëÖİ¼ÙÓìºåÉö¦ãş"};
const unsigned char PY_mb_jiong []={"¾½¾¼ìçåÄ"};
const unsigned char PY_mb_jiu   []={"¾Í¾Å¾Æ¾É¾Ã¾¾¾È¾À¾Ë¾¿¾Â¾Ç¾Ê¾Á¾Ä¾Ì¾ÎôñğÕõíÙÖèÑèê÷İğ¯ãÎà±"};
const unsigned char PY_mb_ju    []={"¾ä¾Ù¾Ş¾Ö¾ß¾à¾â¾ç¾Ó¾Û¾Ğ¾Õ¾Ø¾Ú¾Ü¾å¾Ï¾Ñ¾ÔÇÒ¾İ¹ñ½Û¾ã³µ¾×¾Ò¾á¾æÙÆõ¶ñÕåğêøÜÚñÀì«ï¸é§ÜÄè¢Şäé°ö´ôòÜìöÂåáéÙõáé·÷¶îÒÚªèÛ"};
const unsigned char PY_mb_juan  []={"¾íÈ¦¾ë¾é¾è¾ê¾ì¾îÛ²ïÃîÃïÔáúèğä¸öÁ"};
const unsigned char PY_mb_jue   []={"¾ö¾ø¾õ½Ç¾ô¾ò¾÷¾ï¾ó¾ñ¾ğ½À½ÅèöàåéÓàµõûØãìßÛÇïãâ±çåáÈŞ§àÙÚÜõêæŞØÊ"};
const unsigned char PY_mb_jun   []={"¾ü¾ı¾ù¾ú¿¡¾ş¹ê¿¢¿¥¾û¿£¿¤óŞ÷åñäŞÜ"};
const unsigned char PY_mb_ka    []={"¿¨¿¦¿©¿§ëÌßÇØû"};
const unsigned char PY_mb_kai   []={"¿ª¿«¿­¿®¿¬ÛîØÜï´îøïÇâéâıİÜ"};
const unsigned char PY_mb_kan   []={"¿´¿³¿°¿¯Ç¶¿²¼÷¿±íèê¬Ù©î«İ¨ãÛ"};
const unsigned char PY_mb_kang  []={"¿¹¿»¿¸¿·¿µ¿¶¿ºîÖãÊØø"};
const unsigned char PY_mb_kao   []={"¿¿¿¼¿¾¿½èàêûåêîí"};
const unsigned char PY_mb_ke    []={"¿È¿É¿Ë¿Ã¿Æ¿Å¿Ì¿Î¿Í¿Ç¿Ê¿Á¿Â¿Ä¿ÀºÇã¡á³òòç¼òÂéğñ½îİë´ò¤î§ï¾ïıçæ÷Áğâà¾äÛæì"};
const unsigned char PY_mb_ken   []={"¿Ï¿Ğ¿Ò¿ÑñÌ"};
const unsigned char PY_mb_keng  []={"¿Ó¿Ôï¬"};
const unsigned char PY_mb_kong  []={"¿Õ¿×¿Ø¿ÖÙÅáÇóí"};
const unsigned char PY_mb_kou   []={"¿Ú¿Û¿Ù¿ÜŞ¢ÜÒíîóØßµ"};
const unsigned char PY_mb_ku    []={"¿Ş¿â¿à¿İ¿ã¿ß¿áØÚ÷¼à·Ü¥ç«"};
const unsigned char PY_mb_kua   []={"¿ç¿å¿æ¿ä¿èÙ¨"};
const unsigned char PY_mb_kuai  []={"¿ì¿é¿ê»á¿ëßàØáä«Û¦áöëÚ"};
const unsigned char PY_mb_kuan  []={"¿í¿î÷Å"};
const unsigned char PY_mb_kuang []={"¿ó¿ğ¿ñ¿ò¿ö¿õ¿ï¿ôÚ¿Ú÷æşŞÅÚ²ÛÛêÜßÑ"};
const unsigned char PY_mb_kui   []={"¿÷À¢¿ü¿úÀ£¿û¿ıÀ¡¿ø¿ş¿ùØÑã´Şñî¥õÍñùóñà­åÓêÒİŞã¦à°Ø¸òñÚóÙç"};
const unsigned char PY_mb_kun   []={"À¦À§À¥À¤öïï¿÷Õçûõ«ãÍã§"};
const unsigned char PY_mb_kuo   []={"À«À©À¨ÀªÊÊòÒèé"};
const unsigned char PY_mb_la    []={"À­À²À±À¯À°À®À¬À¶ÂäğøååíÇØİê¹"};
const unsigned char PY_mb_lai   []={"À´ÀµÀ³áÁáâäµäşêãíùïªñ®ô¥"};
const unsigned char PY_mb_lan   []={"À¶À¼ÀÃÀ¹ÀºÀÁÀ¸À¿ÀÂÀÄÀ»À¾À·À½ÀÀé­á°ñÜïçìµî½äí"};
const unsigned char PY_mb_lang  []={"ÀËÀÇÀÈÀÉÀÊÀÆÀÅïüòëİ¹à¥ï¶ãÏİõ"};
const unsigned char PY_mb_lao   []={"ÀÏÀÌÀÎÀÍÀÓÀÔÂäÀÑÀÒÂçÀĞÁÊñìï©õ²îîßëèááÀğì"};
const unsigned char PY_mb_le    []={"ÁËÀÖÀÕÀßØìß·ãî÷¦"};
const unsigned char PY_mb_lei   []={"ÀàÀÛÀáÀ×ÀİÀÕÀŞÀÙÀßÀØÀÜÀÚçĞÚ³ñçõªÙúæĞéÛàÏ"};
const unsigned char PY_mb_leng  []={"ÀäÀâÀãÜ¨ã¶"};
const unsigned char PY_mb_li    []={"ÀïÀëÁ¦Á¢ÀîÀıÁ¨ÀíÀûÀæÀåÀñÀúÀöÀôÀçÀèÀéÀêÀìÀğÀòÀóÀõÀ÷ÀøÀùÀüÀşÁ¡Á£Á¤Á¥Á§Ù³ÙµÛªÛŞÜÂİ°İñğ¿óÒ÷¯çÊõÈòÛï®ã¦å¢ôÏèÀó»Øªß¿íÂæËóöğİğßáûŞ¼äàöâìåèİà¦õ·éöîºæêî¾åÎà¬ö¨÷óòÃæ²"};
const unsigned char PY_mb_lia	[]={"Á©"};
const unsigned char PY_mb_lian  []={"Á¬ÁªÁ·Á«ÁµÁ³Á¶Á´Á²Á¯Á®Á±Á­Á°ó¹çöéçİüöãŞÆäòì¡ñÍå¥ñÏé¬"};
const unsigned char PY_mb_liang []={"Á½ÁÁÁ¾Á¹Á¸ÁºÁ¿Á¼ÁÀÁÂÁ©Á»Ü®ö¦õÔé£÷Ëİ¹"};
const unsigned char PY_mb_liao  []={"ÁËÁÏÁÃÁÄÁÌÁÆÁÎÁÇÁÉÁÅÁÈÁÍÁÊîÉŞ¤ŞÍå¼çÔâ²ğÓàÚ"};
const unsigned char PY_mb_lie   []={"ÁĞÁÑÁÔÁÓÁÒßÖÛøŞæ÷àôóõñÙıä£"};
const unsigned char PY_mb_lin   []={"ÁÖÁÙÁÜÁÚÁ×ÁÛÁŞÁßÁàÁÕÁØÁİåàá×İşôÔ÷ëõïê¥âŞãÁî¬éİì¢ßø"};
const unsigned char PY_mb_ling  []={"ÁíÁîÁìÁãÁåÁáÁéÁëÁäÁèÁêÁâÁæÁçÀâôáòÈÜßç±ê²Û¹ßÊãöèùèÚöìñöàò"};
const unsigned char PY_mb_liu   []={"ÁùÁ÷ÁôÁõÁøÁïÁòÁöÁñÁğÁóÂµÂ½ç¸ï³öÌïÖä¯æòì¼ğÒìÖåŞ"};
const unsigned char PY_mb_long  []={"ÁúÂ£ÁıÁûÂ¡Â¢ÅªÁüÁşÂ¤ÛâëÊççÜ×ãñèĞñªíÃ"};
const unsigned char PY_mb_lou   []={"Â¥Â§Â©ÂªÂ¶Â¦Â¨ÙÍò÷ïÎİäñï÷Ãà¶ğüáĞ"};
const unsigned char PY_mb_lu    []={"Â·Â¶Â¼Â¹Â½Â¯Â¬Â³Â±Â«Â­Â®ÂµÂ°ÂÌÂ²Â¸Â¾ÂºÂ»Â´ÁùöÔèÓäËŞ¤åÖãòéñëªóüéÖéûÛäëÍàà"};
const unsigned char PY_mb_luan  []={"ÂÒÂÑÂĞÂÍÂÏÂÎèïöÇÙõæ®ğ½"};
const unsigned char PY_mb_lue   []={"ÂÔÂÓï²"};
const unsigned char PY_mb_lun   []={"ÂÛÂÖÂÕÂ×ÂÙÂØÂÚàğ"};
const unsigned char PY_mb_luo   []={"ÂäÂŞÂàÂãÂâÀÓÂáÂİÂÜÂåÂæÂßÂç¿©ÜıäğÙùöÃÙÀíÑé¡ŞÛëáñ§Şûãøçóïİâ¤"};
const unsigned char PY_mb_lv    []={"ÂÌÂÊÂÁÂ¿ÂÃÂÅÂËÂÀÂÉÂÈÂÆÂÂÂÇÂÄÙÍëöéµãÌŞÛñÚïù"};
const unsigned char PY_mb_ma    []={"ÂğÂèÂíÂïÂéÂîÄ¨ÂëÂêÂìÄ¦ßéó¡áïæÖè¿"};
const unsigned char PY_mb_mai   []={"ÂòÂôÂõÂñÂóÂöÛ½ö²İ¤"};
const unsigned char PY_mb_man   []={"ÂúÂıÂ÷ÂşÂùÂûÂüÂøÂñÃ¡á£÷©Ü¬òıïÜò©÷´çÏì×"};
const unsigned char PY_mb_mang  []={"Ã¦Ã¢Ã¤Ã§Ã£Ã¥íËÚøòşäİ"};
const unsigned char PY_mb_mao   []={"Ã«Ã°Ã±Ã¨Ã¬Ã®Ã²Ã¯Ã³Ã­ÃªÃ©ë£Üâè£òú÷Öí®êÄêóî¦á¹Ùóó±ì¸ã÷"};
const unsigned char PY_mb_me    []={"Ã´÷á"};
const unsigned char PY_mb_mei   []={"Ã»Ã¿ÃºÃ¾ÃÀÃ¸ÃÃÃ¶Ã¹ÃµÃ¼Ã·ÃÂÃÁÃ½ÃÓÃÄÃÕÄ­áÒâ­ñÇäØä¼ğÌİ®÷ÈïÑé¹"};
const unsigned char PY_mb_men   []={"ÃÅÃÇÃÆŞÑìËí¯îÍ"};
const unsigned char PY_mb_meng  []={"ÃÍÃÎÃÉÃÌÃÏÃËÃÊÃÈÃ¥íæòìÛÂãÂİùó·òµëüô»ô¿Ş«"};
const unsigned char PY_mb_mi    []={"Ã×ÃÜÃÔÃĞÃÛÃÕÃÙÃØÃÖÃİÃÒÃÓÃÚÃÑŞÂ÷ãßäãè÷çìòâ¨åôÚ×ØÂëßåµôÍà×ôé"};
const unsigned char PY_mb_mian  []={"ÃæÃŞÃâÃàÃßÃåÃãÃáÃäëïäÏííãæö¼äÅ"};
const unsigned char PY_mb_miao  []={"ÃëÃçÃíÃîÃèÃéÃêÃìíğçÑç¿åãíµß÷èÂğÅ"};
const unsigned char PY_mb_mie   []={"ÃğÃïßãóúóºØ¿"};
const unsigned char PY_mb_min   []={"ÃñÃòÃôÃöÃóÃõçëíªçÅãÉçäÜåãıö¼÷ªáº"};
const unsigned char PY_mb_ming  []={"ÃûÃ÷ÃüÃùÃúÃøÃËÚ¤î¨êÔÜøäéõ¤"};
const unsigned char PY_mb_miu   []={"ÃıçÑ"};
const unsigned char PY_mb_mo    []={"ÃşÄ¥Ä¨Ä©Ä¤Ä«Ã»ÄªÄ¬Ä§Ä£Ä¦Ä¡Ä®Ä°ÂöÄ­ÍòÎŞÃ°Ä¯ï÷İë÷áÜÔºÙæÖÄ¢ñ¢éâïÒæÆÚÓõöõøâÉñò"};
const unsigned char PY_mb_mou   []={"Ä³Ä±Ä²íøòÖöÊÙ°çÑßè"};
const unsigned char PY_mb_mu    []={"Ä¾Ä¸Ä¶Ä»Ä¿Ä¹ÄÁÄ²Ä£ÄÂÄºÄµÄ´Ä¼Ä½ÄÀÄ·ÀÑîâë¤ÛéãåØïÜÙ"};
const unsigned char PY_mb_na    []={"ÄÇÄÃÄÄÄÉÄÆÄÈÄÅÄÏñÄŞàïÕëÇ"};
const unsigned char PY_mb_nai   []={"ÄËÄÍÄÌÄÎÄÊÄÄİÁÜµèÍØ¾Ù¦"};
const unsigned char PY_mb_nan   []={"ÄÑÄÏÄĞôöàïòïéªà«ëî"};
const unsigned char PY_mb_nang  []={"ÄÒâÎêÙàìß­"};
const unsigned char PY_mb_nao   []={"ÄÖÄÔÄÕÄÓÄ×Ø«îóè§ÛñßÎòÍâ®íĞ"};
const unsigned char PY_mb_ne    []={"ÄØÄÄÄÇÄÅÚ«"};
const unsigned char PY_mb_nei   []={"ÄÚÄÄÄÙÄÇ"};
const unsigned char PY_mb_nen   []={"ÄÛí¥"};
const unsigned char PY_mb_neng  []={"ÄÜ"};
const unsigned char PY_mb_ni    []={"ÄãÄàÄâÄåÄæÄØÄçÄßÄáÄäÄİÄŞîêêÇÛèìòâ¥Ù£âõöòíşì»"};
const unsigned char PY_mb_nian  []={"ÄêÄîÄíÄìÄéÄëÄèÕ³Ø¥ğ¤éıöÓöóÛş"};
const unsigned char PY_mb_niang []={"ÄïÄğ"};
const unsigned char PY_mb_niao  []={"ÄñÄòôÁÜàëåæÕ"};
const unsigned char PY_mb_nie   []={"ÄóÄøÄôÄõÄùÄ÷ÄöÚíŞÁà¿ô«õæò¨Ø¿"};
const unsigned char PY_mb_nin   []={"Äúí¥"};
const unsigned char PY_mb_ning  []={"Å¡ÄıÄşÄûÄüÅ¢Øúå¸ßÌñ÷"};
const unsigned char PY_mb_niu   []={"Å£Å¤Å¦Å¥áğâîæ¤ŞÖ"};
const unsigned char PY_mb_nong  []={"ÅªÅ¨Å©Å§ßæÙ¯"};
const unsigned char PY_mb_nu    []={"Å­Å¬Å«æÛæÀæååó"};
const unsigned char PY_mb_nuan  []={"Å¯"};
const unsigned char PY_mb_nue   []={"Å°Å±ÚÊ"};
const unsigned char PY_mb_nuo   []={"Å²ÅµÅ³Å´ÄÈßöÙĞï»Şù"};
const unsigned char PY_mb_nv    []={"Å®îÏí¤ô¬"};
const unsigned char PY_mb_o     []={"Å¶à¸àŞ"};
const unsigned char PY_mb_ou    []={"Å¼Å»Å·ÅºÅ¸ÇøÅ½Å¹âæê±Ú©ñî"};
const unsigned char PY_mb_pa    []={"ÅÂÅÀÅ¿Å¾°Ò°ÇÅÁÅÃÅÉóáèËİâ"};
const unsigned char PY_mb_pai   []={"ÅÉÅÅÅÄÅÆÆÈÅÇÅÈßßÙ½İå"};
const unsigned char PY_mb_pan   []={"ÅÌÅÎÅĞÅÊÅÏÅËÅÑÅÍ·¬°ãÅÖñáó´ñÈãúŞÕãİõç"};
const unsigned char PY_mb_pang  []={"ÅÔÅÖÅÕÅÓÅÒ°ò°õäèáİåÌó¦"};
const unsigned char PY_mb_pao   []={"ÅÜÅ×ÅÚÅİÅÙÅÛÅØáóŞËâÒğåëã"};
const unsigned char PY_mb_pei   []={"ÅãÅäÅâÅŞÅßÅåÅàÅæÅáì·ïÂàúõ¬ö¬àÎ"};
const unsigned char PY_mb_pen   []={"ÅçÅèäÔ"};
const unsigned char PY_mb_peng  []={"ÅöÅõÅïÅéÅîÅóÅíÅôÅëÅğÅòÅêÅìÅñâñÜ¡ó²àØ"};
const unsigned char PY_mb_pi    []={"ÅúÆ¤ÅûÆ¥Åü±ÙÅ÷Æ¨Æ¢Æ§Æ£Æ¦ÅùÅıÅşÆ¡Æ©Åø·ñõùØ§ÛÜæÇñ±Øòß¨Û¯ê¶èÁî¢òçÜ±ÚüßÁÚéîëâÏî¼Ûıç¢ÚğäÄàèò·ñÔ"};
const unsigned char PY_mb_pian  []={"Æ¬ÆªÆ­Æ«±ã±âôæçÂêúæéëİõäÚÒ"};
const unsigned char PY_mb_piao  []={"Æ±Æ®Æ¯Æ°ÆÓóªİ³æÎî©éèçÎàÑæôØâ"};
const unsigned char PY_mb_pie   []={"Æ³Æ²ÜÖë­"};
const unsigned char PY_mb_pin   []={"Æ·Æ¶Æ¸Æ´ÆµæÉé¯æ°êòò­"};
const unsigned char PY_mb_ping  []={"Æ½Æ¾Æ¿ÆÀÆÁÆ¹Æ¼Æ»Æº·ëæ³öÒèÒÙ·"};
const unsigned char PY_mb_po    []={"ÆÆÆÂÆÄÆÅÆÃÆÈ²´ÆÇÆÓ·±ÆÉóÍğ«îÇÚéÛ¶ê·ØÏçêîŞ"};
const unsigned char PY_mb_pou   []={"ÆÊŞåÙö"};
const unsigned char PY_mb_pu    []={"ÆËÆÌÆ×¸¬ÆÍÆÑÆÏÆÓÆĞÆØÆÎÆÙÆÒÆÔÆÖ±¤ÆÕ±©ïèàÛÙéäßå§ë«õëè±ïäƒW"};
const unsigned char PY_mb_qi    []={"ÆğÆäÆßÆøÆÚÆëÆ÷ÆŞÆïÆûÆåÆæÆÛÆáÆôÆİÆâÆñÆöÆúÆüÆîÆàÆóÆòÆõÆçÆíÆÜÆèÆêÆé»üÆù¼©ÆãÆıÆìì÷ñıæëá¨áªõèİ½Ş­èçí¬ÜÎÜùİÂÜ»ãàØ½÷¢Ù¹éÊàÒòÓôëØÁì¥ç÷÷èçùòàÛßè½İİíÓä¿ìóêÈç²"};
const unsigned char PY_mb_qia   []={"Ç¡¿¨ÆşÇ¢ñÊİÖ÷Ä"};
const unsigned char PY_mb_qian  []={"Ç°Ç®Ç§Ç£Ç³Ç©Ç·Ç¦Ç¶Ç¥Ç¨Ç¯Ç¬Ç´Ç«Ç±Ç¸ÏËÇ¤Ç²Ç­ÇµÇªá©îÔå½óéŞçåºÙ»ã»ã¥í©ò¯ÜÍİ¡ç×ÙİÜ·ÚäëÉÜçèıêùå¹"};
const unsigned char PY_mb_qiang []={"Ç¿Ç¹Ç½ÇÀÇ»ÇºÇ¼Ç¾½«òŞõÄê¨ñßãŞìÁïêïºïÏôÇéÉæÍ"};
const unsigned char PY_mb_qiao  []={"ÇÅÇÆÇÃÇÉÇÌÇÂ¿ÇÇÊÇËÇÄÇÎÇÏÈ¸ÇÇÇÈÇÍÇÁéÔÜñõÎíÍã¾ÚÛ÷³ã¸çØÚ½Øä"};
const unsigned char PY_mb_qie   []={"ÇĞÇÒÇÓÇÔÇÑÆöÛ§ôòã«ïÆæªóæã»Ù¤êü"};
const unsigned char PY_mb_qin   []={"Ç×ÇÙÇÖÇÚÇÜÇŞÇØÇÛÇßÇİÇÕßÄñûñæôÀÜËäÚâÛàºòûàßŞìéÕï·"};
const unsigned char PY_mb_qing  []={"ÇëÇáÇåÇàÇéÇçÇâÇãÇìÇæÇêÇ×ÇäÇèàõö¥éÑóäÜÜòß÷ôóÀöëíàôì"};
const unsigned char PY_mb_qiong []={"ÇîÇíõ¼ñ·ÚöòËÜäöÆóÌ"};
const unsigned char PY_mb_qiu   []={"ÇóÇòÇïÇğÇö³ğÇñÇôÇõ¹êé±òÇôÃôÜòøÛÏåÏÙ´ò°êäöúáìäĞ÷üåÙ"};
const unsigned char PY_mb_qu    []={"È¥È¡ÇøÈ¢ÇşÇúÇ÷È¤ÇüÇıÇùÇûÈ£Ğçó½Ş¾ìîŞ¡íáÛ¾Ú°ğ¶ãÖôğñ³áé÷ñè³ë¬êïòĞëÔöÄá«ÜÄ"};
const unsigned char PY_mb_quan  []={"È«È¨È°È¦È­È®ÈªÈ¯È§È¬È©îıóÜç¹Ú¹éúî°÷ÜãªòéÜõ"};
const unsigned char PY_mb_que   []={"È´È±È·È¸È³ÈµÈ²È¶ãÚã×í¨"};
const unsigned char PY_mb_qun   []={"ÈºÈ¹åÒ÷å"};
const unsigned char PY_mb_ran   []={"È¾È¼È»È½÷×ÜÛòÅ"};
const unsigned char PY_mb_rang  []={"ÈÃÈÂÈ¿ÈÁÈÀğ¦ìü"};
const unsigned char PY_mb_rao   []={"ÈÄÈÆÈÅÜéèãæ¬"};
const unsigned char PY_mb_re    []={"ÈÈÈôÈÇßö"};
const unsigned char PY_mb_ren   []={"ÈËÈÎÈÌÈÏÈĞÈÊÈÍÈÑÈÒÈÉâ¿éíØğÜóİØñÅïş"};
const unsigned char PY_mb_reng  []={"ÈÓÈÔ"};
const unsigned char PY_mb_ri    []={"ÈÕ"};
const unsigned char PY_mb_rong  []={"ÈİÈŞÈÚÈÜÈÛÈÙÈÖÈØÈßÈ×éÅáõáÉëÀòî"};
const unsigned char PY_mb_rou   []={"ÈâÈàÈáôÛõå÷·"};
const unsigned char PY_mb_ru    []={"ÈçÈëÈêÈåÈãÈéÈìÈèÈäÈæİêñàï¨àéçÈå¦Ş¸ò¬äáä²"};
const unsigned char PY_mb_ruan  []={"ÈíÈîëÃ"};
const unsigned char PY_mb_rui   []={"ÈğÈïÈñî£ÜÇò¸èÄŞ¨"};
const unsigned char PY_mb_run   []={"ÈòÈó"};
const unsigned char PY_mb_ruo   []={"ÈôÈõÙ¼óè"};
const unsigned char PY_mb_sa    []={"ÈöÈ÷ÈøêıØíØ¦ìªëÛ"};
const unsigned char PY_mb_sai   []={"ÈûÈùÈúË¼Èüàç"};
const unsigned char PY_mb_san   []={"ÈıÉ¢É¡ÈşâÌôÖë§ö±"};
const unsigned char PY_mb_sang  []={"É£É¥É¤òªíßŞú"};
const unsigned char PY_mb_sao   []={"É¨É©É¦É§ÉÒÜ£öşëıçÒğş"};
const unsigned char PY_mb_se    []={"É«É¬ÉªÈûØÄï¤ğ£"};
const unsigned char PY_mb_sen   []={"É­"};
const unsigned char PY_mb_seng  []={"É®"};
const unsigned char PY_mb_sha   []={"É±É³É¶É´ÉµÉ°É²É¯ÏÃÉ·É¼àÄßşöèö®ï¡ğğôÄêıì¦"};
const unsigned char PY_mb_shai  []={"É¹É¸É«õ§"};
const unsigned char PY_mb_shan  []={"É½ÉÁÉÀÉÆÉÈÉ¼É¾É¿µ¥Éº²ôÉÄÕ¤É»µ§ÉÅÉÂÉÇÉÃÉÉæÓóµÜÏìøõÇÛ·äú÷­æ©ØßæóğŞëşÚ¨îÌô®Ûï"};
const unsigned char PY_mb_shang []={"ÉÏÉËÉĞÉÌÉÍÉÎÉÊÌÀÉÑìØõüç´éäÛğ"};
const unsigned char PY_mb_shao  []={"ÉÙÉÕÉÓÉÚÉ×ÉÒÉÔÉÛÉØÉÜÉÖÕÙÇÊÜæÛ¿äûô¹òÙóâ"};
const unsigned char PY_mb_she   []={"ÉçÉäÉßÉèÉàÉãÉáÕÛÉæÉŞÉâÉåÉİì¨ØÇî´â¦÷êäÜÙÜ"};
const unsigned char PY_mb_shen  []={"ÉíÉìÉîÉôÉñÉõÉøÉöÉóÉêÉòÉğÉë²ÎÉéÊ²ÉïÉ÷İØôÖİ·Ú·ÚÅïòé©äÉò×ßÓëÏ"};
const unsigned char PY_mb_sheng []={"ÉùÊ¡Ê£ÉúÉıÉşÊ¤Ê¢Ê¥ÉûÉü³ËêÉäÅíòóÏáÓ"};
const unsigned char PY_mb_shi   []={"ÊÇÊ¹Ê®Ê±ÊÂÊÒÊĞÊ¯Ê¦ÊÔÊ·Ê½Ê¶Ê­Ê¸Ê°ÊºÊ»Ê¼ËÆĞêÊ¾Ê¿ÊÀÊÁ³×ÊÃÊÄÊÅÊÆÊ²Ö³ÖÅÊÈÊÉÊ§ÊÊÊËÊÌÊÍÊÎÊÏÊ¨Ê³ÊÑÊ´ÊÓÊµÊ©ÊªÊ«Ê¬õ¹İªÛõîæóÂöåöõêÛéøİéóßìÂÚÖß±õ§ó§"};
const unsigned char PY_mb_shou  []={"ÊÖÊÜÊÕÊ×ÊØÊİÊÚÊŞÊÛÊìÊÙô¼á÷ç·"};
const unsigned char PY_mb_shu   []={"ÊéÊ÷ÊıÊìÊäÊáÊåÊôÊøÊõÊöÊñÊòÊóÊçÊêÊëÊßÊèÊùÊúÊûÊüÊíÊşË¡ÊàÊîÊâÊãÊïÊğÊææ­Şóïø"};
const unsigned char PY_mb_shua  []={"Ë¢Ë£à§"};
const unsigned char PY_mb_shuai []={"Ë¤Ë¦ÂÊË§Ë¥ó°"};
const unsigned char PY_mb_shuan []={"Ë¨Ë©ãÅäÌ"};
const unsigned char PY_mb_shuang[]={"Ë«ËªË¬ãñæ×"};
const unsigned char PY_mb_shui  []={"Ë®Ë­Ë¯Ë°Ëµ"};
const unsigned char PY_mb_shun  []={"Ë³Ë±Ë²Ë´"};
const unsigned char PY_mb_shuo  []={"ËµÊıË¶Ë¸Ë·Ş÷åùéÃİôîå"};
const unsigned char PY_mb_si    []={"ËÄËÀË¿ËºËÆË½Ë»Ë¼ËÂË¾Ë¹Ê³ËÅ²ŞËÁËÇËÃËÈñêæáÙîòÏØËãáïÈãôóÓßĞğ¸æ¦ÛÌçÁìëäùÙ¹"};
const unsigned char PY_mb_song  []={"ËÍËÉËÊËÎËÌËĞËËËÏñµİ¿äÁã¤áÔÚ¡áÂâì"};
const unsigned char PY_mb_sou   []={"ËÒËÑËÓËÔàÕà²ì¬ÛÅŞ´ïËâÈî¤äÑòôËÓ"};
const unsigned char PY_mb_su    []={"ËØËÙËßËÜËŞË×ËÕËàËÚËÖËõËİËÛãºóùö¢öÕÙíà¼ÚÕİøä³"};
const unsigned char PY_mb_suan  []={"ËáËãËââ¡"};
const unsigned char PY_mb_sui   []={"ËêËæËéËäËëËìÄòËåËèËçËíËîíõÚÇå¡åäìİİ´î¡"};
const unsigned char PY_mb_sun   []={"ËïËğËñé¾İ¥â¸áøöÀ"};
const unsigned char PY_mb_suo   []={"ËùËõËøËöË÷ËóËòÉ¯ËôêıíüàÊßïèøàÂæ¶ôÈ"};
const unsigned char PY_mb_ta    []={"ËûËıËüÌ¤ËşËúÍØÌ¡Ì¢Ì£äâõÁ÷£í³é½äğåİîèãËàª"};
const unsigned char PY_mb_tai   []={"Ì«Ì§Ì¨Ì¬Ì¥Ì¦Ì©ÌªÌ­ìÆëÄõÌß¾öØîÑŞ·Û¢ææ"};
const unsigned char PY_mb_tan   []={"Ì¸Ì¾Ì½Ì²µ¯Ì¼Ì¯Ì¶Ì°Ì³ÌµÌºÌ¹Ì¿Ì±Ì·Ì®Ì´Ì»Û°ê¼ìşîãïÄå£ïâñû"};
const unsigned char PY_mb_tang  []={"ÌÉÌËÌÃÌÇÌÀÌÁÌÌÌÈÌÊÌÆÌÂÌÄÌÅó«éÌôÊõ±è©ïÛÙÎâ¼äçñíàûï¦ó¥"};
const unsigned char PY_mb_tao   []={"Ì×ÌÍÌÓÌÒÌÖÌÔÌÎÌÏÌÕÌĞÌÑØ»ßûä¬èº÷Òß¶ìâ"};
const unsigned char PY_mb_te    []={"ÌØìıí«ï«ß¯"};
const unsigned char PY_mb_teng  []={"ÌÛÌÚÌÙÌÜëø"};
const unsigned char PY_mb_ti    []={"ÌáÌæÌåÌâÌßÌãÌêÌŞÌİÌàÌäÌéÌçÌèÌëõ®ğÃç°ç¾ÙÃñÓåÑÜèã©"};
const unsigned char PY_mb_tian  []={"ÌìÌïÌíÌîÌğÌòÌñÌóµèŞİîäãÙãÃéåî±"};
const unsigned char PY_mb_tiao  []={"ÌõÌøÌôµ÷ÌöÌ÷ö¶óÔìöòè÷ØÙ¬ñ»öæÜæôĞ"};
const unsigned char PY_mb_tie   []={"ÌúÌùÌûİÆ÷Ñ"};
const unsigned char PY_mb_ting  []={"ÌıÍ£Í¦ÌüÍ¤Í§Í¥Í¢ÌşÍ¡ÜğİãæÃèèòÑöªî®îú"};
const unsigned char PY_mb_tong  []={"Í¬Í¨Í´Í­Í°Í²Í±Í³Í¯Í®Í©Í«¶²¶±ÍªäüÜíÙÚíÅá¼âúÙ¡àÌÛí"};
const unsigned char PY_mb_tou   []={"Í·ÍµÍ¸Í¶î×÷»"};
const unsigned char PY_mb_tu    []={"ÍÁÍ¼ÍÃÍ¿ÍÂÍºÍ»Í½Í¹Í¾ÍÀÜ¢İ±İËîÊõ©"};
const unsigned char PY_mb_tuan  []={"ÍÅÍÄî¶ŞÒåè"};
const unsigned char PY_mb_tui   []={"ÍÈÍÆÍËÍÊÍÇÍÉìÕß¯"};
const unsigned char PY_mb_tun   []={"ÍÌÍÍÍÊÍÎ¶ÚÙÛâ½êÕëà"};
const unsigned char PY_mb_tuo   []={"ÍÏÍÑÍĞÍ×ÍÔÍØÍÕÍÖÍÙÍÒÍÓÆÇØ±Ù¢ÛçâÕãûèØèŞéÒõÉóêõ¢íÈö¾"};
const unsigned char PY_mb_wa    []={"ÍÚÍßÍÜÍÛÍŞÍİ°¼ÍàØôæ´ëğ"};
const unsigned char PY_mb_wai   []={"ÍâÍááË"};
const unsigned char PY_mb_wan   []={"ÍêÍòÍíÍëÍæÍäÍìÍåÍèÍóÍğÍñÍéÍçÍãÍïÃäÍîÂûİ¸ëäòêçºÜ¹çşæıØàîµİÒ"};
const unsigned char PY_mb_wang  []={"ÍûÍüÍõÍùÍøÍöÍ÷ÍúÍôÍıÃ¢Øèã¯éş÷Í"};
const unsigned char PY_mb_wei   []={"ÎªÎ»Î´Î§Î¹Î¸Î¢Î¶Î²Î±ÍşÎ°ÎÀÎ£Î¥Î¯ÎºÎ¨Î¬Î·Î©Î¤Î¡ÎµÎ½Î¾Î«Î³Î¿Î¦Î®Î­Î¼ÒÅİÚàøôºöÛæ¸åÔãÇÚñãíçâä¶á¡áËÚóÚÃä¢ÙËâ«â¬áÍê¦è¸ì¿ìĞÛ×Ş±ğô"};
const unsigned char PY_mb_wen   []={"ÎÊÎÄÎÅÎÈÎÂÎÇÎÃÎÆÎÁÎÉãëãÓØØö©è·"};
const unsigned char PY_mb_weng  []={"ÎÌÎËÎÍİîŞ³"};
const unsigned char PY_mb_wo    []={"ÎÒÎÕÎÑÎÔÎÎÎÖÎÏÎĞÎÓÙÁá¢ö»ë¿İ«à¸ä×íÒ"};
const unsigned char PY_mb_wu    []={"ÎŞÎåÎİÎïÎèÎíÎóÎæÎÛÎòÎğÎÙÎäÎìÎñÎØÎéÎâÎçÎáÎêÎÚÎã¶ñÎÜÎßÎ×ÎîÎàÎëåüòÚêõå»Ø£âäÚãÚùâèæğì¶öÈØõè»ğÍæÄåÃğíÜÌìÉßíâĞğÄ÷ùä´ÛØ"};
const unsigned char PY_mb_xi    []={"Î÷Ï´Ï¸ÎüÏ·ÏµÏ²Ï¯Ï¡ÏªÏ¨ÎıÏ¥Ï¢Ï®Ï§Ï°ÎûÏ¦Ï¤ÎùÎõÏ£Ï­ÎşÎúÎôÏ±ÎøÏ³Ï©À°ÎöÏ¶ÆÜÏ«Ï¬òáŞÉä»İßâ¾åïçôæÒìùÙâôâñ¶ìûÙÒäÀİûô¸õèõµì¤ğªó¬ôËÜçáãÚôÛ­ßñêØó£ì¨éØãÒôÑìäêêİ¾÷ûñÓôª"};
const unsigned char PY_mb_xia   []={"ÏÂÏÅÏÄÏ¿ÏºÏ¹Ï¼ÏÁÏ»ÏÀÏ½ÏÃÏ¾»£áòåÚè¦èÔíÌóÁ÷ïßÈ"};
const unsigned char PY_mb_xian  []={"ÏÈÏßÏØÏÖÏÔÏÆÏĞÏ×ÏÓÏİÏÕÏÊÏÒÏÎÏÚÏŞÏÌÏÇÏÉÏÙÏÍÏËÏÜÏÏÏÑÏÛÏ³¼ûÜÈŞºá­ğïİ²ôÌæµò¹áıììÙşìŞõĞõÑõ£åßë¯ğÂóÚö±"};
const unsigned char PY_mb_xiang []={"ÏëÏòÏóÏîÏìÏãÏçÏàÏñÏäÏïÏíÏâÏá½µÏèÏéÏğÏêÏæÏåÜ¼İÙâÃâÔæøç½ó­öß÷Ï"};
const unsigned char PY_mb_xiao  []={"Ğ¡Ğ¦ÏûÏ÷ÏúÏôĞ§ÏüÏşĞ¤Ğ¢ÏõĞ¥ÏöÏøÏùĞ£æçßØäìåĞèÉç¯ÏıáÅóïèÕóã÷ÌòÙ"};
const unsigned char PY_mb_xie   []={"Ğ´Ğ©Ğ¬ĞªĞ±ÑªĞ»Ğ¶Ğ®Ğ¼Ğ·ĞºĞ¸Ğ¹Ğ¨Ğ°Ğ­ĞµĞ³Ğ«Ğ¯Ğ²½âÆõÒ¶ç¥ò¡çÓâ³é¿âİß¢ÙÉå¬äÍÙôéÇåâŞ¯õóÛÆÛÄ"};
const unsigned char PY_mb_xin   []={"ĞÂĞÄĞÀĞÅĞ¾Ğ½Ğ¿ĞÁÑ°ĞÆĞÃì§Ø¶İ·Ü°öÎê¿ïâ"};
const unsigned char PY_mb_xing  []={"ĞÔĞĞĞÍĞÎĞÇĞÑĞÕĞÈĞÌĞÓĞËĞÒĞÏĞÉĞÊÊ¡íÊã¬ÜşÚêß©Üô"};
const unsigned char PY_mb_xiong []={"ĞØĞÛĞ×ĞÖĞÜĞÚĞÙÜº"};
const unsigned char PY_mb_xiu   []={"ĞŞĞâĞåĞİĞßËŞĞáĞäĞãĞà³ôßİá¶âÊâÓäåğ¼õ÷÷Û"};
const unsigned char PY_mb_xu    []={"ĞíĞëĞèĞéĞêĞîĞøĞòĞğĞóĞõĞöĞçĞìĞñĞ÷ÓõĞïĞôĞæôÚÛÃèòä°Ş£çïÛ×äªñãõ¯Ú¼äÓìãíìí¹"};
const unsigned char PY_mb_xuan  []={"Ñ¡ĞüĞıĞşĞûĞúĞùÑ¤Ñ£Ñ¢È¯ÙØìÅÚÎİæŞïãùäÖäöè¯é¸êÑìÓíÛîçïàğç"};
const unsigned char PY_mb_xue   []={"Ñ§Ñ©ÑªÑ¥Ñ¨Ï÷Ñ¦õ½àå÷¨í´"};
const unsigned char PY_mb_xun   []={"Ñ°Ñ¶Ñ¬ÑµÑ­Ñ³Ñ®Ñ²Ñ¸Ñ±Ñ´Ñ·Ñ«»çÑ¯¿£ÙãÛ÷Ü÷Ş¦Ş¹á¾áßâ´âşä­ä±êÖõ¸öàÛ¨ñ¿"};
const unsigned char PY_mb_ya    []={"Ñ½Ñ¹ÑÀÑºÑ¿Ñ¼ÔşÑÂÑÆÑÇÑÄÑ¾ÑÅÑÃÑ»ÑÈÑÁØóÛëŞëá¬åÂæ«çğèâë²í¼íığéñâ"};
const unsigned char PY_mb_yan   []={"ÑÛÑÌÑØÑÎÑÔÑİÑÏÑÊÑÍÑ×ÑÚÑáÑçÑÒÑĞÑÓÑßÑéÑŞÑËÑâÑãÑäÑåÑæÑÑÑÜÑèÑàÑÕÑÖÑÉÑÙØÉİÎ÷ÊçüäÙìÍóÛØÍÙğâûéÜäÎÚİÙÈëÙêÌãÆÙ²Û±Û³åûáÃæÌî»õ¦÷Ğ÷úÇ¦ÒóÚçÜ¾ãÕëçØß"};
const unsigned char PY_mb_yang  []={"ÑùÑøÑòÑóÑöÑïÑíÑõÑ÷ÑîÑúÑôÑêÑëÑìÑğÑñì¾í¦áà÷±ãóòÕìÈâó"};
const unsigned char PY_mb_yao   []={"ÒªÒ¡Ò©Ò§ÑüÒ¤Ò¨ÑûÑıÒ¥Ò£Ò¦ÑşÒ«Ò¢Ô¿½ÄØ²Ø³ßºáÊáæçÛçòèÃé÷ê×ëÈğÎñº÷¥Å±ÌÕÔ¼ï¢"};
const unsigned char PY_mb_ye    []={"Ò²Ò¹ÒµÒ°Ò¶Ò¯Ò³ÒºÒ´Ò¸Ò±Ò­Ò®ÑÊÒ·Ò¬Ğ°ÚËÚşêÊìÇŞŞîôØÌ"};
const unsigned char PY_mb_yi    []={"Ò»ÒÔÒÑÒÚÒÂÒÆÒÀÒ×Ò½ÒÒÒÇÒàÒÎÒæÒĞÒÌÒíÒëÒÁÉßÒÅÊ³°¬ÒÈÒÉÒÊÒËÒìÒÍÒ¼ÒÏÒêÒ¾Ò¿ÒÓÒîÒÕÒÖÒïÒØ¶êÒÙÎ²ÒÛÒÜÒİÒŞÒßÒÃÒáÒâÒãÒäÒåÒÄÒçÒèÒéâøğêï×ñ¯âùæäì½ìÚôıñ´ì¥á»ÛİéìàÉß×Ü²àæØæÚ±âÂäôØıßŞğùâ¢íôôàŞÄÜÓÜèØîÙ«êİîÆçËåÆØ×ã¨÷ğôèß®ŞÈòæÛüŞÚáÚŞ²ß½éóïî"};
const unsigned char PY_mb_yin   []={"ÒòÒıÓ¡ÒøÒôÒûÒõÒşÒñÒ÷ÒüÒúÒğÒùÒóÒöÑÌÜ§Û´à³â¹Ø·ö¸ßÅÛßáşÛóö¯ò¾ë³î÷ñ¿ñ«ä¦Üá"};
const unsigned char PY_mb_ying  []={"Ó¦Ó²Ó°ÓªÓ­Ó³Ó¬Ó®Ó¥Ó¢Ó±Ó¨Ó¯Ó¤Ó£Ó§Ó«Ó©İÓéºİöñ¨ÜãğĞëôİºè¬Û«àÓŞüçøäŞäëÙøó¿å­âßÜşò£"};
const unsigned char PY_mb_yo    []={"Ó´Óıà¡"};
const unsigned char PY_mb_yong  []={"ÓÃÓ¿ÓÀÓµÓ¼ÓÂÓºÓ½Ó¾Ó¶Ó»Ó¸Ó¹Ó·ÓÁÙ¸ÛÕÜ­à¯ã¼çßïŞğ®÷«÷Ó"};
const unsigned char PY_mb_you   []={"ÓĞÓÖÓÉÓÒÓÍÓÎÓ×ÓÅÓÑÓËÓÇÓÈÓÌÓÕÓÆÓÊÓÏÓÓÓÄÓÔØüØÕÙ§İ¬İ¯İµßÏàóå¶èÖéàë»îğğàòÄòÊòööÏ÷î÷øòøôí"};
const unsigned char PY_mb_yu    []={"ÓëÓÚÓûÓãÓêÓàÓöÓïÓúÓüÓñÓæÓèÓşÓıÓŞÓğÓİÓéÓÙÓßÓìÓíÓîÓØÓáÓâÓòÓóÓô¹ÈÓõÓÛÓ÷ÓøÓùÓäÖàÓåÎ¾ÓÜÓçÔ¡Ô¢Ô£Ô¤Ô¥Ô¦ÎµåıáÎö§âÅãĞñ¾ğÁæ¥ŞíñÁêìô§ô¨ö¹İ÷ìÏîÚÚÄæúì¶óÄè¤Ø®í²ì£Ù¶ØñàôğÖâ×êÅİÇğõÚÍå÷àöğöìÙâÀØ¹ìÛëéáüİÒòâòõ"};
const unsigned char PY_mb_yuan  []={"Ô¶Ô±ÔªÔºÔ²Ô­Ô¸Ô°Ô®Ô³Ô¹Ô©Ô´ÔµÔ¬Ô¨Ô·Ô«Ô§Ô¯à÷ö½éÚæÂë¼íóğ°ŞòÜ¾ãäè¥ó¢óîÜ«Ûù"};
const unsigned char PY_mb_yue   []={"ÔÂÔ½Ô¼Ô¾ÔÄÀÖÔÀÔÃÔ»ËµÔÁÔ¿å®îáë¾ÙßèİéĞ"};
const unsigned char PY_mb_yun   []={"ÔÆÔËÔÎÔÊÔÈÔÏÔÉÔĞÔÅÔÌÔÍÔÇÔ±ìÙëµã¢ã³Û©Ü¿óŞè¹êÀáñéæç¡"};
const unsigned char PY_mb_za    []={"ÔÓÔÒÕ¦ÔÑÔúÔÛßÆŞÙ"};
const unsigned char PY_mb_zai   []={"ÔÚÔÙÔÖÔØÔÔÔ×ÔÕáÌçŞ×Ğ"};
const unsigned char PY_mb_zan   []={"ÔÛÔİÔÜÔŞô¢ôõôØè¶ŞÙêÃöÉ"};
const unsigned char PY_mb_zang  []={"ÔàÔáÔß²Øê°æàŞÊ"};
const unsigned char PY_mb_zao   []={"ÔçÔìÔâÔãÔîÔïÔæÔäÔêÔåÔíÔëÔèÔéßğ"};
const unsigned char PY_mb_ze    []={"ÔòÔğÔñÔóÕ¦²àóåô·àıåÅßõØÆê¾óĞØÓ"};
const unsigned char PY_mb_zei   []={"Ôô"};
const unsigned char PY_mb_zen   []={"ÔõÚÚ"};
const unsigned char PY_mb_zeng  []={"ÔöÔùÔ÷Ôø×ÛçÕîÀêµï­"};
const unsigned char PY_mb_zha   []={"ÔúÕ¨ÔüÕ¢Õ£Õ¥Õ§ÔşÕ©ÔûÔıÕ¡Şêß¸ßåßîâªíÄğäòÆ÷ş²éÀ¯Õ¤Õ¦à©é«×õ"};
const unsigned char PY_mb_zhai  []={"ÕªÕ­Õ®Õ«Õ¯ÔñµÔÕ¬²à¼ÀíÎñ©"};
const unsigned char PY_mb_zhan  []={"Õ¾Õ¼Õ½ÕµÕ´Õ³Õ±Õ¹Õ»Õ²²üÕºÕ¿ÕÀÕ¶Õ·Õ¸Õ°ÚŞŞøì¹"};
const unsigned char PY_mb_zhang []={"ÕÅÕÂ³¤ÕÊÕÌÕÉÕÆÕÇÕËÕÁÕÈÕÃÕÄÕÍÕÎÕÏØëæÑá¤Ûµè°áÖâ¯ó¯"};
const unsigned char PY_mb_zhao  []={"ÕÒ×ÅÕÕÕĞÕÖ×¦Õ×³¯ÕÑÕÓÕØ³°ÕÙÕÔèşîÈóÉÚ¯ßú"};
const unsigned char PY_mb_zhe   []={"×ÅÕâÕßÕÛÕÚÕİÕÜÕáÕàÕŞÕãèÏéüô÷ß¡ğÑíİñŞòØÚØ"};
const unsigned char PY_mb_zhen  []={"ÕæÕóÕòÕëÕğÕíÕñÕåÕäÕîÕïÕçÕèÕéÕêÕìçÇİèìõóğéôé»ğ¡êâëŞğ²ëÓä¥èåî³ÛÚé©"};
const unsigned char PY_mb_zheng []={"ÕıÕûÕöÕùÕõÕ÷ÕúÖ¤Ö¢Ö£ÕüÕôÕøÕşÖ¡á¿îÛï£óİÚºáç¶¡öë"};
const unsigned char PY_mb_zhi   []={"Ö»Ö®Ö±ÖªÖÆÖ¸Ö½Ö§Ö¥Ö¦ÖÉÖ¨Ö©ÖÊÖ«Ö¬Ö­ÖËÖ¯Ö°ÖÌÖ²µÖÖ³Ö´ÖµÖ¶Ö·ÖÇÖÍÖ¹ÖºÖÎÖ¼ÖÏÖ¾Ö¿ÖÀÖÁÖÂÖÃÖÄÊ¶ÖÅÊÏÖÈàùŞıíéèäè×éòâåìíòÎëùö£Û¤èÙåéÜÆìóåëğºôêõÙëÕæïéùğëÚìõÜïôÛúêŞØ´õ¥õôõÅèÎ¼¿"};
const unsigned char PY_mb_zhong []={"ÖĞÖØÖÖÖÓÖ×ÖÚÖÕÖÑÖÒÖÙÖÔõàô±ó®ïñÚ£âì"};
const unsigned char PY_mb_zhou  []={"ÖÜÖŞÖåÖàÖİÖáÖÛÖçÖèÖæÖßÖâÖãÖäôíëĞæûİ§ßúíØç§ô¦æ¨ôü"};
const unsigned char PY_mb_zhu   []={"×¡Ö÷ÖíÖñÖêÖóÖşÖøÖéÖëÖìÖîÖïÖğÖòÖôÖõÖöÖùÖúÖûÖüÖı×¢×£×¤Øùäóä¨ğñôãÜïÜÑéÍô¶èÌóçìÄÙªîùğæä¾ñÒõî÷æÛ¥éÆóÃÊôÊõ"};
const unsigned char PY_mb_zhua  []={"×¥×¦ÎÎ"};
const unsigned char PY_mb_zhuai []={"×§×ª"};
const unsigned char PY_mb_zhuan []={"×ª×¨×©×¬´«×«×­ò§âÍßùãç"};
const unsigned char PY_mb_zhuang[]={"×°×²×¯×³×®×´´±×±Ù×ŞÊí°"};
const unsigned char PY_mb_zhui  []={"×·×¹×º×¶×¸×µæíã·çÄö¿"};
const unsigned char PY_mb_zhun  []={"×¼×»ÍÍëÆñ¸"};
const unsigned char PY_mb_zhuo  []={"×½×À×Å×Ä×¾×Æ×Ç×¿×Á½É×Â×ÃßªìÌåªÚÂä·äÃÙ¾ïíìúí½"};
const unsigned char PY_mb_zi    []={"×Ö×Ô×Ó×Ï×Ñ×Ê×ËÖ¨×Ò×Ğ×É×Î×Õ×Ì×ÍÚÑÜëáÑæ¢æÜç»è÷ê¢êßí§íöïÅïöñèóÊôÒôôö¤ö·öö÷Ú×Èõş"};
const unsigned char PY_mb_zong  []={"×Ü×İ×Ú×Ø×Û×Ù××ÙÌôÕèÈëê"};
const unsigned char PY_mb_zou   []={"×ß×á×à×ŞöíÛ¸ÚîæãÚÁ"};
const unsigned char PY_mb_zu    []={"×é×å×ã×è×â×æ×çİÏïß×äÙŞ"};
const unsigned char PY_mb_zuan  []={"×ê×ë×¬ß¬çÚõò"};
const unsigned char PY_mb_zui   []={"×î×ì×í×ï¶Ñ¾×õşŞ©"};
const unsigned char PY_mb_zun   []={"×ğ×ñß¤é×÷®"};
const unsigned char PY_mb_zuo   []={"×ö×÷×ø×ó×ù×òÔä×ôÚèßòâôëÑìñ´é×ÁàÜóĞõ¡×õ"};

/*
*********************************************************************************************************
*	                         Æ´Òô¼ìË÷µÄ½á¹¹ÌåÊı×é
*********************************************************************************************************
*/
struct PinYinPCB const PYRankTwoList_a[]=
{
	{"",PY_mb_a},
	{"i",PY_mb_ai},
	{"n",PY_mb_an},
	{"ng",PY_mb_ang},
	{"o",PY_mb_ao}
};


struct PinYinPCB const PYRankTwoList_b[]=
{
	{"a",PY_mb_ba},
	{"ai",PY_mb_bai},
	{"an",PY_mb_ban},
	{"ang",PY_mb_bang},
	{"ao",PY_mb_bao},
	{"ei",PY_mb_bei},
	{"en",PY_mb_ben},
	{"eng",PY_mb_beng},
	{"i",PY_mb_bi},
	{"ian",PY_mb_bian},
	{"iao",PY_mb_biao},
	{"ie",PY_mb_bie},
	{"in",PY_mb_bin},
	{"ing",PY_mb_bing},
	{"o",PY_mb_bo},
	{"u",PY_mb_bu}
};

struct PinYinPCB const PYRankTwoList_c[]=
{
	{"a",PY_mb_ca},
	{"ai",PY_mb_cai},
	{"an",PY_mb_can},
	{"ang",PY_mb_cang},
	{"ao",PY_mb_cao},
	{"e",PY_mb_ce},
	{"eng",PY_mb_ceng},
	{"ha",PY_mb_cha},
	{"hai",PY_mb_chai},
	{"han",PY_mb_chan},
	{"hang",PY_mb_chang},
	{"hao",PY_mb_chao},
	{"he",PY_mb_che},
	{"hen",PY_mb_chen},
	{"heng",PY_mb_cheng},
	{"hi",PY_mb_chi},
	{"hong",PY_mb_chong},
	{"hou",PY_mb_chou},
	{"hu",PY_mb_chu},
	{"huai",PY_mb_chuai},
	{"huan",PY_mb_chuan},
	{"huang",PY_mb_chuang},
	{"hui",PY_mb_chui},
	{"hun",PY_mb_chun},
	{"huo",PY_mb_chuo},
	{"i",PY_mb_ci},
	{"ong",PY_mb_cong},
	{"ou",PY_mb_cou},
	{"u",PY_mb_cu},
	{"uan",PY_mb_cuan},
	{"ui",PY_mb_cui},
	{"un",PY_mb_cun},
	{"uo",PY_mb_cuo}
};

struct PinYinPCB const PYRankTwoList_d[]=
{
	{"a   ",PY_mb_da},
	{"ai",PY_mb_dai},
	{"an",PY_mb_dan},
	{"ang",PY_mb_dang},
	{"ao",PY_mb_dao},
	{"e",PY_mb_de},
	{"eng",PY_mb_deng},
	{"i",PY_mb_di},
	{"ian",PY_mb_dian},
	{"iao",PY_mb_diao},
	{"ie",PY_mb_die},
	{"ing",PY_mb_ding},
	{"iu",PY_mb_diu},
	{"ong",PY_mb_dong},
	{"ou",PY_mb_dou},
	{"u",PY_mb_du},
	{"uan",PY_mb_duan},
	{"ui",PY_mb_dui},
	{"un",PY_mb_dun},
	{"uo",PY_mb_duo}
};

struct PinYinPCB const PYRankTwoList_e[]=
{
	{"",PY_mb_e},
	{"n",PY_mb_en},
	{"r",PY_mb_er}
};

struct PinYinPCB const PYRankTwoList_f[]=
{
	{"a",PY_mb_fa},
	{"an",PY_mb_fan},
	{"ang",PY_mb_fang},
	{"ei",PY_mb_fei},
	{"en",PY_mb_fen},
	{"eng",PY_mb_feng},
	{"o",PY_mb_fo},
	{"ou",PY_mb_fou},
	{"u",PY_mb_fu}
};

struct PinYinPCB const PYRankTwoList_g[]=
{
	{"a",PY_mb_ga},
	{"ai",PY_mb_gai},
	{"an",PY_mb_gan},
	{"ang",PY_mb_gang},
	{"ao",PY_mb_gao},
	{"e",PY_mb_ge},
	{"ei",PY_mb_gei},
	{"en",PY_mb_gan},
	{"eng",PY_mb_geng},
	{"ong",PY_mb_gong},
	{"ou",PY_mb_gou},
	{"u",PY_mb_gu},
	{"ua",PY_mb_gua},
	{"uai",PY_mb_guai},
	{"uan",PY_mb_guan},
	{"uang",PY_mb_guang},
	{"ui",PY_mb_gui},
	{"un",PY_mb_gun},
	{"uo",PY_mb_guo}
};

struct PinYinPCB const PYRankTwoList_h[]=
{
	{"a",PY_mb_ha},
	{"ai",PY_mb_hai},
	{"an",PY_mb_han},
	{"ang",PY_mb_hang},
	{"ao",PY_mb_hao},
	{"e",PY_mb_he},
	{"ei",PY_mb_hei},
	{"en",PY_mb_hen},
	{"eng",PY_mb_heng},
	{"ong",PY_mb_hong},
	{"ou",PY_mb_hou},
	{"u",PY_mb_hu},
	{"ua",PY_mb_hua},
	{"uai",PY_mb_huai},
	{"uan",PY_mb_huan},
	{"uang ",PY_mb_huang},
	{"ui",PY_mb_hui},
	{"un",PY_mb_hun},
	{"uo",PY_mb_huo}
};

struct PinYinPCB const PYRankTwoList_i[]=
{
	"",PY_mb_space
};

struct PinYinPCB const PYRankTwoList_j[]=
{
	{"i",PY_mb_ji},
	{"ia",PY_mb_jia},
	{"ian",PY_mb_jian},
	{"iang",PY_mb_jiang},
	{"iao",PY_mb_jiao},
	{"ie",PY_mb_jie},
	{"in",PY_mb_jin},
	{"ing",PY_mb_jing},
	{"iong",PY_mb_jiong},
	{"iu",PY_mb_jiu},
	{"u",PY_mb_ju},
	{"uan",PY_mb_juan},
	{"ue",PY_mb_jue},
	{"un",PY_mb_jun}
};

struct PinYinPCB const PYRankTwoList_k[]=
{
	{"a",PY_mb_ka},
	{"ai",PY_mb_kai},
	{"an",PY_mb_kan},
	{"ang",PY_mb_kang},
	{"ao",PY_mb_kao},
	{"e",PY_mb_ke},
	{"en",PY_mb_ken},
	{"eng",PY_mb_keng},
	{"ong",PY_mb_kong},
	{"ou",PY_mb_kou},
	{"u",PY_mb_ku},
	{"ua",PY_mb_kua},
	{"uai",PY_mb_kuai},
	{"uan",PY_mb_kuan},
	{"uang",PY_mb_kuang},
	{"ui",PY_mb_kui},
	{"un",PY_mb_kun},
	{"uo",PY_mb_kuo}
};

struct PinYinPCB const PYRankTwoList_l[]=
{
	{"a",PY_mb_la},
	{"ai",PY_mb_lai},
	{"an",PY_mb_lan},
	{"ang",PY_mb_lang},
	{"ao",PY_mb_lao},
	{"e",PY_mb_le},
	{"ei",PY_mb_lei},
	{"eng",PY_mb_leng},
	{"i",PY_mb_li},
	{"ian",PY_mb_lian},
	{"iang",PY_mb_liang},
	{"iao",PY_mb_liao},
	{"ie",PY_mb_lie},
	{"in",PY_mb_lin},
	{"ing",PY_mb_ling},
	{"iu",PY_mb_liu},
	{"ong",PY_mb_long},
	{"ou",PY_mb_lou},
	{"u",PY_mb_lu},
	{"uan",PY_mb_luan},
	{"ue",PY_mb_lue},
	{"un",PY_mb_lun},
	{"uo",PY_mb_luo},
	{"v",PY_mb_lv}
};

struct PinYinPCB const PYRankTwoList_m[]=
{
	{"a",PY_mb_ma},
	{"ai",PY_mb_mai},
	{"an",PY_mb_man},
	{"ang",PY_mb_mang},
	{"ao",PY_mb_mao},
	{"e",PY_mb_me},
	{"ei",PY_mb_mei},
	{"en",PY_mb_men},
	{"eng",PY_mb_meng},
	{"i",PY_mb_mi},
	{"ian",PY_mb_mian},
	{"iao",PY_mb_miao},
	{"ie",PY_mb_mie},
	{"in",PY_mb_min},
	{"ing",PY_mb_ming},
	{"iu",PY_mb_miu},
	{"o",PY_mb_mo},
	{"ou",PY_mb_mou},
	{"u",PY_mb_mu}
};

struct PinYinPCB const PYRankTwoList_n[]=
{
	{"a",PY_mb_na},
	{"ai",PY_mb_nai},
	{"an",PY_mb_nan},
	{"ang",PY_mb_nang},
	{"ao",PY_mb_nao},
	{"e",PY_mb_ne},
	{"ei",PY_mb_nei},
	{"en",PY_mb_nen},
	{"eng",PY_mb_neng},
	{"i",PY_mb_ni},
	{"ian",PY_mb_nian},
	{"iang",PY_mb_niang},
	{"iao",PY_mb_niao},
	{"ie",PY_mb_nie},
	{"in",PY_mb_nin},
	{"ing",PY_mb_ning},
	{"iu",PY_mb_niu},
	{"ong",PY_mb_nong},
	{"u",PY_mb_nu},
	{"uan",PY_mb_nuan},
	{"ue",PY_mb_nue},
	{"uo",PY_mb_nuo},
	{"v",PY_mb_nv}
};

struct PinYinPCB const PYRankTwoList_o[]=
{
	{"",PY_mb_o},
	{"u",PY_mb_ou}
};

struct PinYinPCB const PYRankTwoList_p[]=
{
	{"a",PY_mb_pa},
	{"ai",PY_mb_pai},
	{"an",PY_mb_pan},
	{"ang",PY_mb_pang},
	{"ao",PY_mb_pao},
	{"ei",PY_mb_pei},
	{"en",PY_mb_pen},
	{"eng",PY_mb_peng},
	{"i",PY_mb_pi},
	{"ian",PY_mb_pian},
	{"iao",PY_mb_piao},
	{"ie",PY_mb_pie},
	{"in",PY_mb_pin},
	{"ing",PY_mb_ping},
	{"o",PY_mb_po},
	{"ou",PY_mb_pou},
	{"u",PY_mb_pu}
};

struct PinYinPCB const PYRankTwoList_q[]=
{
	{"i",PY_mb_qi},
	{"ia",PY_mb_qia},
	{"ian",PY_mb_qian},
	{"iang",PY_mb_qiang},
	{"iao",PY_mb_qiao},
	{"ie",PY_mb_qie},
	{"in",PY_mb_qin},
	{"ing",PY_mb_qing},
	{"iong",PY_mb_qiong},
	{"iu",PY_mb_qiu},
	{"u",PY_mb_qu},
	{"uan",PY_mb_quan},
	{"ue",PY_mb_que},
	{"un",PY_mb_qun}
};

struct PinYinPCB const PYRankTwoList_r[]=
{
	{"an",PY_mb_ran},
	{"ang",PY_mb_rang},
	{"ao",PY_mb_rao},
	{"e",PY_mb_re},
	{"en",PY_mb_ren},
	{"eng",PY_mb_reng},
	{"i",PY_mb_ri},
	{"ong",PY_mb_rong},
	{"ou",PY_mb_rou},
	{"u",PY_mb_ru},
	{"uan",PY_mb_ruan},
	{"ui",PY_mb_rui},
	{"un",PY_mb_run},
	{"uo",PY_mb_ruo}
};

struct PinYinPCB const PYRankTwoList_s[]=
{
	{"a",PY_mb_sa},
	{"ai",PY_mb_sai},
	{"an",PY_mb_san},
	{"ang",PY_mb_sang},
	{"ao",PY_mb_sao},
	{"e",PY_mb_se},
	{"en",PY_mb_sen},
	{"eng",PY_mb_seng},
	{"ha",PY_mb_sha},
	{"hai",PY_mb_shai},
	{"han",PY_mb_shan},
	{"hang ",PY_mb_shang},
	{"hao",PY_mb_shao},
	{"he",PY_mb_she},
	{"hen",PY_mb_shen},
	{"heng",PY_mb_sheng},
	{"hi",PY_mb_shi},
	{"hou",PY_mb_shou},
	{"hu",PY_mb_shu},
	{"hua",PY_mb_shua},
	{"huai",PY_mb_shuai},
	{"huan",PY_mb_shuan},
	{"huang",PY_mb_shuang},
	{"hui",PY_mb_shui},
	{"hun",PY_mb_shun},
	{"huo",PY_mb_shuo},
	{"i",PY_mb_si},
	{"ong",PY_mb_song},
	{"ou",PY_mb_sou},
	{"u",PY_mb_su},
	{"uan",PY_mb_suan},
	{"ui",PY_mb_sui},
	{"un",PY_mb_sun},
	{"uo",PY_mb_suo}
};

struct PinYinPCB const PYRankTwoList_t[]=
{
	{"a",PY_mb_ta},
	{"ai",PY_mb_tai},
	{"an",PY_mb_tan},
	{"ang",PY_mb_tang},
	{"ao",PY_mb_tao},
	{"e",PY_mb_te},
	{"eng",PY_mb_teng},
	{"i",PY_mb_ti},
	{"ian",PY_mb_tian},
	{"iao",PY_mb_tiao},
	{"ie",PY_mb_tie},
	{"ing",PY_mb_ting},
	{"ong",PY_mb_tong},
	{"ou",PY_mb_tou},
	{"u",PY_mb_tu},
	{"uan",PY_mb_tuan},
	{"ui",PY_mb_tui},
	{"un",PY_mb_tun},
	{"uo",PY_mb_tuo}
};

struct PinYinPCB const PYRankTwoList_u[]=
{
	{"",PY_mb_space}
};

struct PinYinPCB const PYRankTwoList_v[]=
{
	{"",PY_mb_space}
};

struct PinYinPCB const PYRankTwoList_w[]=
{
	{"a",PY_mb_wa},
	{"ai",PY_mb_wai},
	{"an",PY_mb_wan},
	{"ang",PY_mb_wang},
	{"ei",PY_mb_wei},
	{"en",PY_mb_wen},
	{"eng",PY_mb_weng},
	{"o",PY_mb_wo},
	{"u",PY_mb_wu}
};

struct PinYinPCB const PYRankTwoList_x[]=
{
	{"i",PY_mb_xi},
	{"ia",PY_mb_xia},
	{"ian",PY_mb_xiao},
	{"iang",PY_mb_xiang},
	{"iao",PY_mb_xiao},
	{"ie",PY_mb_xie},
	{"in",PY_mb_xin},
	{"ing",PY_mb_xing},
	{"iong",PY_mb_xiong},
	{"iu",PY_mb_xiu},
	{"u",PY_mb_xu},
	{"uan",PY_mb_xuan},
	{"ue",PY_mb_xue},
	{"un",PY_mb_xun}
};

struct PinYinPCB const PYRankTwoList_y[]=
{
	{"a",PY_mb_ya},
	{"an",PY_mb_yan},
	{"ang",PY_mb_yang},
	{"ao",PY_mb_yao},
	{"e",PY_mb_ye},
	{"i",PY_mb_yi},
	{"in",PY_mb_yin},
	{"ing",PY_mb_ying},
	{"o",PY_mb_yo},
	{"ong",PY_mb_yong},
	{"ou",PY_mb_you},
	{"u",PY_mb_yu},
	{"uan",PY_mb_yuan},
	{"ue",PY_mb_yue},
	{"un",PY_mb_yun}
};

struct PinYinPCB const PYRankTwoList_z[]=
{
	{"a",PY_mb_za},
	{"ai",PY_mb_zai},
	{"an",PY_mb_zan},
	{"ang",PY_mb_zang},
	{"ao",PY_mb_zao},
	{"e",PY_mb_ze},
	{"ei",PY_mb_zei},
	{"en",PY_mb_zen},
	{"eng",PY_mb_zeng},
	{"ha",PY_mb_zha},
	{"hai",PY_mb_zhai},
	{"han",PY_mb_zhan},
	{"hang",PY_mb_zhang},
	{"hao",PY_mb_zhao},
	{"he",PY_mb_zhe},
	{"hen",PY_mb_zhen},
	{"heng",PY_mb_zheng},
	{"hi",PY_mb_zhi},
	{"hong",PY_mb_zhong},
	{"hou",PY_mb_zhou},
	{"hu",PY_mb_zhu},
	{"hua",PY_mb_zhua},
	{"huai",PY_mb_zhuai},
	{"huan",PY_mb_zhuan},
	{"huang",PY_mb_zhuang},
	{"hui",PY_mb_zhui},
	{"hun",PY_mb_zhun},
	{"huo",PY_mb_zhuo},
	{"i",PY_mb_zi},
	{"ong",PY_mb_zong},
	{"ou",PY_mb_zou},
	{"u",PY_mb_zu},
	{"uan",PY_mb_zuan},
	{"ui",PY_mb_zui},
	{"un",PY_mb_zun},
	{"uo",PY_mb_zuo}
};

struct PinYinPCB const PYRankTwoList_end[]=
{
	"",	PY_mb_space
};

/*
*********************************************************************************************************
*	                         Æ´Òô¼ìË÷µÄ½á¹¹ÌåÊı×éµÄÖ¸Õë
*********************************************************************************************************
*/
struct PinYinPCB const *PYRankThreeList[]=
{  
	PYRankTwoList_a,
	PYRankTwoList_b,
	PYRankTwoList_c,
	PYRankTwoList_d,
	PYRankTwoList_e,
	PYRankTwoList_f,
	PYRankTwoList_g,
	PYRankTwoList_h,
	PYRankTwoList_i,
	PYRankTwoList_j,
	PYRankTwoList_k,
	PYRankTwoList_l,
	PYRankTwoList_m,
	PYRankTwoList_n,
	PYRankTwoList_o,
	PYRankTwoList_p,
	PYRankTwoList_q,
	PYRankTwoList_r,
	PYRankTwoList_s,
	PYRankTwoList_t,
	PYRankTwoList_u,
	PYRankTwoList_v,
	PYRankTwoList_w,
	PYRankTwoList_x,
	PYRankTwoList_y,
	PYRankTwoList_z,
	PYRankTwoList_end
};

/*
*********************************************************************************************************
*	º¯ Êı Ãû: PYSearch
*	¹¦ÄÜËµÃ÷: ¼ìË÷Æ´ÒôµÄº¯Êı,Ê¹ÓÃºÜ¼òµ¥£¬Ö»ĞèÊäÈëÆ´Òô¾ÍĞĞ·µ»ØÕâ¸öÆ´Òô¶ÔÓ¦µÄºº×Ö¸öÊı¡£
*	ĞÎ    ²Î£ºmsg   Æ´Òô×Ö·û´®
*             num   ·µ»Ø´ËÆ´Òô¶ÔÓ¦µÄºº×Ö¸öÊı
*	·µ »Ø Öµ: Èç¹ûÕâ¸öÆ´Òô´æÔÚºº×ÖÓëÆä¶ÔÓ¦£¬·µ»Ø¼ìË÷µ½µÄºº×ÖµÄÖ¸Õë£¬Èç¹ûÃ»ÓĞ£¬·µ»Ø¿ÕÖ¸Õë
*********************************************************************************************************
*/										
char *PYSearch(unsigned char *msg , int *num)
{
	unsigned char count=0;
	unsigned char i=0;
	/*
		ÀıÈç¡®b'£¬ÒÔ¶ÁÒôÎª¡¯b'¿ªÍ·µÄËùÓĞºº×Ö
		b'µÄÏÂÒ»¸ö¡®c'£¬ÒÔ¶ÁÒôÎª¡¯c'¿ªÍ·µÄËùÓĞºº×Ö
		Í¨¹ıÕâ±È½ÏÁ½¸öÊı¾İµÄ´óĞ¡¿ÉÒÔµÃµ½¡¯b'µÄËùÓĞµÄÔªÒô+¸¨Òô
	*/
	struct PinYinPCB const *headpcb; 		
	struct PinYinPCB const *tailpcb;		
											
	while(msg[count] != 0) count++;			  /* ¼ÆËã¼ìË÷µÄÆ´ÒôµÄ×Ö½ÚÊı     */	
	
	for(i = 0; i < count; i++)				  /* ¼ì²é¼ìË÷µÄÆ´ÒôÊÇ·ñ·ûºÏ¹æ·¶ */
	{
		if((msg[i] >= 'a') && (msg[i]<='z'))  /* ÔÚÕâ¸öÇø¼äµÄÊı¾İÓĞĞ§       */
		{
			continue;
		}								   	  /* ÊäÈëµÄÊı¾İ·Ç·¨£¬·µ»Ø¿ÕÖ¸Õë */
		else
		{
		    return '\0';
		}
	}
	
	/* ÊäÈëµÄÊı¾İ·Ç·¨£¬·µ»Ø¿ÕÖ¸Õë */
	if((*msg == 'i')||(*msg == 'u')||(*msg == 'v')||(*msg == '\0'))	
	{
	    return '\0';
	}
	
	/* ÒÔ¶ÁÒôÎª*msg¿ªÍ·µÄËùÓĞÆ´Òô¼ìË÷ */
	tailpcb = PYRankThreeList[*msg - 'a'];	
	
 	/* ÒÔ¶ÁÒôÎª*msg+1¿ªÍ·µÄËùÓĞÆ´Òô¼ìË÷ */
	headpcb = PYRankThreeList[*msg - 'a' + 1];
	
	for(; tailpcb < headpcb; tailpcb++)
	{
		
		/* ¼ì²éÊäÈëµÄÆ´ÒôÓë¼ìË÷½á¹¹ÌåÖĞµÄÆ´ÒôÊÇ·ñÒ»ÖÂ */
		for(i = 0; i < count - 1; i++)				
		{	
			if(*((*tailpcb).PYSerList+i) != msg[i+1])
			{
				break;
			}
		}
		
		/* Ò»ÖÂ£¬·µ»ØÖ¸Õë */
		if(i == (count - 1))	 					
		{
			/* ÌØ±ğ×¢ÒâÏÂÃæÕâ¸öº¯Êı£¬ÒòÎªUTF-8±àÂë¸ñÊ½µÄºº×ÖÊÇ3¸ö×Ö½Ú */
			*num = strlen((const char *)(*tailpcb).PYRankOneList) / 3;
			return (char *)(*tailpcb).PYRankOneList;
		}

	}
	
	/* ·ñÕß·µ»Ø¿ÕµÄÖ¸Õë */
	return '\0';								
}

/***************************** °²¸»À³µç×Ó www.armfly.com (END OF FILE) *********************************/
