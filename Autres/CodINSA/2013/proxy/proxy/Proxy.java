/*   1:    */ package proxy;
/*   2:    */ 
/*   3:    */ import ai.AbstractAI;
/*   4:    */ import command.Command;
/*   5:    */ import common.MapView;
/*   6:    */ import common.MapView.Transform;
/*   7:    */ import common.Util;
/*   8:    */ import common.Util.Converter;
/*   9:    */ import genbridge.BaseBasicData;
/*  10:    */ import genbridge.BaseFullData;
/*  11:    */ import genbridge.BaseInitData;
/*  12:    */ import genbridge.CoordData;
/*  13:    */ import genbridge.CountryInitData;
/*  14:    */ import genbridge.Data;
/*  15:    */ import genbridge.InitData;
/*  16:    */ import genbridge.PlaneBasicData;
/*  17:    */ import genbridge.PlaneFullData;
/*  18:    */ import genbridge.PlaneStateData;
/*  19:    */ import genbridge.ProgressAxisData;
/*  20:    */ import genbridge.ProgressAxisInitData;
/*  21:    */ import genbridge.RequestData;
/*  22:    */ import java.util.HashMap;
/*  23:    */ import java.util.Iterator;
/*  24:    */ import java.util.List;
/*  25:    */ import java.util.Map;
/*  26:    */ import java.util.Set;
/*  27:    */ import model.AbstractBase;
/*  28:    */ import model.Base;
/*  29:    */ import model.Base.BasicView;
/*  30:    */ import model.Base.FullView;
/*  31:    */ import model.Coord.Unique;
/*  32:    */ import model.Country;
/*  33:    */ import model.Country.Request;
/*  34:    */ import model.Country.View;
/*  35:    */ import model.Plane;
/*  36:    */ import model.Plane.BasicView;
/*  37:    */ import model.Plane.FullView;
/*  38:    */ import model.Plane.State;
/*  39:    */ import model.Plane.Type;
/*  40:    */ import model.ProgressAxis;
/*  41:    */ import org.slf4j.Logger;
/*  42:    */ import org.slf4j.LoggerFactory;
/*  43:    */ 
/*  44:    */ public class Proxy
/*  45:    */ {
/*  46:    */   private IncomingData idm;
/*  47:    */   private CommandSender cm;
/*  48:    */   private AbstractAI client_ai;
/*  49:    */   private Map<Integer, Base> all_bases;
/*  50:    */   private Map<Integer, Base> ai_bases;
/*  51:    */   private Map<Integer, Base> other_visible_bases;
/*  52:    */   private Map<Integer, Base> other_notvisible_bases;
/*  53:    */   private Map<Integer, Plane> ai_planes;
/*  54:    */   private Map<Integer, Plane> killed_planes;
/*  55:    */   private Map<Integer, Plane> ennemy_planes;
/*  56:    */   private Map<Integer, ProgressAxis> map_axis;
/*  57:    */   private Country ai_country;
/*  58:    */   private double mapWidth;
/*  59:    */   private double mapHeight;
/*  60:    */   private int player_id;
/*  61:    */   private int numFrame;
/*  62: 55 */   public static final Logger log = LoggerFactory.getLogger(Proxy.class);
/*  63:    */   
/*  64:    */   public Proxy(String ip, int port, AbstractAI ai)
/*  65:    */   {
/*  66: 65 */     this.client_ai = ai;
/*  67: 66 */     this.idm = new IncomingData(ip, port, this);
/*  68: 67 */     this.ai_planes = new HashMap();
/*  69: 68 */     this.killed_planes = new HashMap();
/*  70: 69 */     this.ennemy_planes = new HashMap();
/*  71: 70 */     this.all_bases = new HashMap();
/*  72: 71 */     this.ai_bases = new HashMap();
/*  73: 72 */     this.other_visible_bases = new HashMap();
/*  74: 73 */     this.other_notvisible_bases = new HashMap();
/*  75: 74 */     this.map_axis = new HashMap();
/*  76:    */     
/*  77: 76 */     this.idm.retrieveInitialData();
/*  78:    */     
/*  79: 78 */     this.player_id = this.idm.getPlayerId();
/*  80:    */     
/*  81: 80 */     this.cm = new CommandSender(ip, port + 1, this.idm.getIdConnection(), this);
/*  82: 81 */     this.cm.start();
/*  83:    */   }
/*  84:    */   
/*  85:    */   void setInitData(InitData d)
/*  86:    */   {
/*  87: 91 */     for (BaseInitData b : d.bases)
/*  88:    */     {
/*  89: 93 */       Base base = new Base(b.base_id, new Coord.Unique(b.posit.x, b.posit.y));
/*  90: 94 */       base.isAiObject = true;
/*  91: 95 */       this.other_notvisible_bases.put(Integer.valueOf(base.id), base);
/*  92: 96 */       this.all_bases.put(Integer.valueOf(base.id), base);
/*  93:    */     }
/*  94: 98 */     this.mapWidth = d.mapWidth;
/*  95: 99 */     this.mapHeight = d.mapHeight;
/*  96:101 */     for (ProgressAxisInitData a : d.progressAxis) {
/*  97:102 */       if ((this.all_bases.containsKey(Integer.valueOf(a.base1_id))) && (this.all_bases.containsKey(Integer.valueOf(a.base2_id))))
/*  98:    */       {
/*  99:104 */         ProgressAxis pa = new ProgressAxis(a.id, (Base)this.all_bases.get(Integer.valueOf(a.base1_id)), (Base)this.all_bases.get(Integer.valueOf(a.base2_id)));
/* 100:105 */         pa.isAiObject = true;
/* 101:106 */         this.map_axis.put(Integer.valueOf(a.id), pa);
/* 102:    */       }
/* 103:    */       else
/* 104:    */       {
/* 105:109 */         log.error("One or both of the base " + a.base1_id + " and " + a.base2_id + " are unknown. Failed to add the axis");
/* 106:    */       }
/* 107:    */     }
/* 108:111 */     this.ai_country = new Country(d.myCountry.country_id, new Coord.Unique(d.myCountry.country.x, d.myCountry.country.y));
/* 109:112 */     this.ai_country.isAiObject = true;
/* 110:    */   }
/* 111:    */   
/* 112:    */   private void updateBases(Data d)
/* 113:    */   {
/* 114:137 */     for (BaseFullData b : d.owned_bases)
/* 115:    */     {
/* 116:139 */       int base_id = b.basic_info.base_id;
/* 117:140 */       Base base = (Base)this.all_bases.get(Integer.valueOf(base_id));
/* 118:141 */       if (base == null) {
/* 119:142 */         throw new Error("The base with id " + base_id + " does not exist");
/* 120:    */       }
/* 121:143 */       new Object(); {}
/* 122:145 */       if (this.other_notvisible_bases.containsKey(Integer.valueOf(base.id)))
/* 123:    */       {
/* 124:147 */         base.fullViewInSync = false;
/* 125:148 */         this.other_notvisible_bases.remove(Integer.valueOf(base.id));
/* 126:    */       }
/* 127:150 */       if (this.other_visible_bases.containsKey(Integer.valueOf(base.id))) {
/* 128:151 */         this.other_visible_bases.remove(Integer.valueOf(base.id));
/* 129:    */       }
/* 130:153 */       this.ai_bases.put(Integer.valueOf(base_id), base);
/* 131:    */     }
/* 132:156 */     for (BaseFullData b : d.not_owned_visible_bases)
/* 133:    */     {
/* 134:158 */       int base_id = b.basic_info.base_id;
/* 135:159 */       Base base = (Base)this.all_bases.get(Integer.valueOf(base_id));
/* 136:160 */       if (base == null) {
/* 137:161 */         throw new Error("The base with id " + base_id + " does not exist");
/* 138:    */       }
/* 139:162 */       new Object(); {}
/* 140:164 */       if (this.ai_bases.containsKey(Integer.valueOf(base.id))) {
/* 141:165 */         this.ai_bases.remove(Integer.valueOf(base.id));
/* 142:    */       }
/* 143:166 */       if (this.other_notvisible_bases.containsKey(Integer.valueOf(base.id)))
/* 144:    */       {
/* 145:168 */         base.fullViewInSync = false;
/* 146:169 */         this.other_notvisible_bases.remove(Integer.valueOf(base.id));
/* 147:    */       }
/* 148:171 */       this.other_visible_bases.put(Integer.valueOf(base_id), base);
/* 149:    */     }
/* 150:174 */     for (BaseBasicData b : d.not_owned_not_visible_bases)
/* 151:    */     {
/* 152:176 */       int base_id = b.base_id;
/* 153:177 */       Base base = (Base)this.all_bases.get(Integer.valueOf(base_id));
/* 154:178 */       if (base == null) {
/* 155:179 */         throw new Error("The base with id " + base_id + " does not exist");
/* 156:    */       }
/* 157:180 */       new Object(); {}
/* 158:182 */       if (this.ai_bases.containsKey(Integer.valueOf(base.id)))
/* 159:    */       {
/* 160:184 */         this.ai_bases.remove(Integer.valueOf(base.id));
/* 161:185 */         base.fullViewInSync = false;
/* 162:    */       }
/* 163:187 */       if (this.other_visible_bases.containsKey(Integer.valueOf(base.id)))
/* 164:    */       {
/* 165:189 */         this.other_visible_bases.remove(Integer.valueOf(base.id));
/* 166:190 */         base.fullViewInSync = false;
/* 167:    */       }
/* 168:193 */       this.other_notvisible_bases.put(Integer.valueOf(base_id), base);
/* 169:    */     }
/* 170:    */   }
/* 171:    */   
/* 172:    */   private void updatePlanes(Data d)
/* 173:    */   {
/* 174:206 */     this.killed_planes.putAll(this.ai_planes);
/* 175:207 */     for (Plane p : this.ai_planes.values()) {
/* 176:208 */       p.exists = false;
/* 177:    */     }
/* 178:209 */     this.ai_planes.clear();
/* 179:243 */     for (PlaneFullData p : d.owned_planes)
/* 180:    */     {
/* 181:245 */       if (p.basic_info.ai_id != this.player_id) {
/* 182:246 */         log.warn("A not owned plane is in the owned ones: may generate errors");
/* 183:    */       }
/* 184:248 */       if (this.killed_planes.containsKey(Integer.valueOf(p.basic_info.plane_id)))
/* 185:    */       {
/* 186:250 */         Plane plane = (Plane)this.killed_planes.remove(Integer.valueOf(p.basic_info.plane_id));
/* 187:251 */         new Object(); {};
/* 188:252 */         this.ai_planes.put(Integer.valueOf(p.basic_info.plane_id), plane);
/* 189:    */       }
/* 190:    */       else
/* 191:    */       {
/* 192:257 */         Plane plane = new Plane(p.basic_info.plane_id, new Coord.Unique(p.basic_info.posit.x, p.basic_info.posit.y), Plane.Type.get(p.basic_info.planeTypeId));
/* 193:258 */         plane.isAiObject = true;
/* 194:259 */         new Object(); {};
/* 195:260 */         this.ai_planes.put(Integer.valueOf(plane.id), plane);
/* 196:    */       }
/* 197:    */     }
/* 198:264 */     for (PlaneBasicData p : d.not_owned_planes)
/* 199:    */     {
/* 200:266 */       if (p.ai_id == this.player_id) {
/* 201:267 */         log.warn("An owned plane is in the not owned ones: may generate errors");
/* 202:    */       }
/* 203:269 */       if (this.ennemy_planes.containsKey(Integer.valueOf(p.plane_id)))
/* 204:    */       {
/* 205:271 */         Plane plane = (Plane)this.ennemy_planes.get(Integer.valueOf(p.plane_id));
/* 206:272 */         new Object(); {}
/* 207:    */       }
/* 208:    */       else
/* 209:    */       {
/* 210:276 */         Plane plane = new Plane(p.plane_id, new Coord.Unique(p.posit.x, p.posit.y), Plane.Type.get(p.planeTypeId));
/* 211:277 */         plane.isAiObject = true;
/* 212:278 */         new Object(); {};
/* 213:279 */         this.ennemy_planes.put(Integer.valueOf(plane.id), plane);
/* 214:    */       }
/* 215:    */     }
/* 216:    */   }
/* 217:    */   
/* 218:    */   private void updateAxis(Data d)
/* 219:    */   {
/* 220:290 */     for (ProgressAxisData a : d.progressAxis) {
/* 221:292 */       if (this.map_axis.containsKey(Integer.valueOf(a.id)))
/* 222:    */       {
/* 223:294 */         ProgressAxis progAxis = (ProgressAxis)this.map_axis.get(Integer.valueOf(a.id));
/* 224:    */         
/* 225:296 */         progAxis.ratio1 = a.progressBase1;
/* 226:297 */         progAxis.ratio2 = a.progressBase2;
/* 227:    */       }
/* 228:    */     }
/* 229:    */   }
/* 230:    */   
/* 231:    */   private void updateCountry(Data d)
/* 232:    */   {
/* 233:309 */     for (Iterator localIterator = this.ai_country.productionLine.keySet().iterator(); localIterator.hasNext();)
/* 234:    */     {
/* 235:309 */       int i = ((Integer)localIterator.next()).intValue();
/* 236:310 */       if (!d.productionLine.contains(Integer.valueOf(i))) {
/* 237:314 */         ((Country.Request)this.ai_country.productionLine.remove(Integer.valueOf(i))).timeBeforePlaneBuilt = 0.0D;
/* 238:    */       }
/* 239:    */     }
/* 240:317 */     for (RequestData rd : d.productionLine) {
/* 241:320 */       if (this.ai_country.productionLine.containsKey(Integer.valueOf(rd.requestId)))
/* 242:    */       {
/* 243:321 */         ((Country.Request)this.ai_country.productionLine.get(Integer.valueOf(rd.requestId))).timeBeforePlaneBuilt = rd.timeBeforePlaneBuilt;
/* 244:    */       }
/* 245:    */       else
/* 246:    */       {
/* 247:323 */         Country tmp181_178 = this.ai_country;tmp181_178.getClass();this.ai_country.productionLine.put(Integer.valueOf(rd.requestId), new Country.Request(tmp181_178, rd.requestId, rd.timeBeforePlaneBuilt, Plane.Type.get(rd.planeTypeId)));
/* 248:    */       }
/* 249:    */     }
/* 250:    */   }
/* 251:    */   
/* 252:    */   void updateProxyData(Data d)
/* 253:    */   {
/* 254:336 */     this.numFrame = d.numFrame;
/* 255:    */     
/* 256:338 */     updateBases(d);
/* 257:339 */     updatePlanes(d);
/* 258:340 */     updateAxis(d);
/* 259:341 */     updateCountry(d);
/* 260:    */     
/* 261:343 */     this.cm.newFrame();
/* 262:    */   }
/* 263:    */   
/* 264:    */   public int getNumFrame()
/* 265:    */   {
/* 266:351 */     return this.numFrame;
/* 267:    */   }
/* 268:    */   
/* 269:    */   public double getMapWidth()
/* 270:    */   {
/* 271:358 */     return this.mapWidth;
/* 272:    */   }
/* 273:    */   
/* 274:    */   public double getMapHeight()
/* 275:    */   {
/* 276:365 */     return this.mapHeight;
/* 277:    */   }
/* 278:    */   
/* 279:    */   public MapView<Integer, Plane.FullView> getKilledPlanes()
/* 280:    */   {
/* 281:376 */     return Util.view(this.killed_planes);
/* 282:    */   }
/* 283:    */   
/* 284:    */   public MapView<Integer, Plane.FullView> getMyPlanes()
/* 285:    */   {
/* 286:386 */     return Util.view(this.ai_planes);
/* 287:    */   }
/* 288:    */   
/* 289:    */   public MapView<Integer, Plane.BasicView> getEnnemyPlanes()
/* 290:    */   {
/* 291:397 */     new MapView.Transform(this.ennemy_planes, new Util.Converter()
/* 292:    */     {
/* 293:    */       public Plane.BasicView convert(Plane src)
/* 294:    */       {
/* 295:400 */         return src.restrictedView();
/* 296:    */       }
/* 297:    */     });
/* 298:    */   }
/* 299:    */   
/* 300:    */   public MapView<Integer, Base.BasicView> getAllBases()
/* 301:    */   {
/* 302:412 */     new MapView.Transform(this.all_bases, new Util.Converter()
/* 303:    */     {
/* 304:    */       public Base.BasicView convert(Base src)
/* 305:    */       {
/* 306:415 */         if (Proxy.this.other_notvisible_bases.containsKey(Integer.valueOf(src.id))) {
/* 307:416 */           return src.restrictedView();
/* 308:    */         }
/* 309:418 */         return src.view();
/* 310:    */       }
/* 311:    */     });
/* 312:    */   }
/* 313:    */   
/* 314:    */   public MapView<Integer, Base.FullView> getMyBases()
/* 315:    */   {
/* 316:430 */     return Util.view(this.ai_bases);
/* 317:    */   }
/* 318:    */   
/* 319:    */   public MapView<Integer, Base.FullView> getVisibleBase()
/* 320:    */   {
/* 321:440 */     Map<Integer, Base> res = new HashMap(this.ai_bases);
/* 322:441 */     res.putAll(this.other_visible_bases);
/* 323:442 */     return Util.view(res);
/* 324:    */   }
/* 325:    */   
/* 326:    */   public MapView<Integer, Base.FullView> getNotOwnedAndVisibleBases()
/* 327:    */   {
/* 328:452 */     return Util.view(this.other_visible_bases);
/* 329:    */   }
/* 330:    */   
/* 331:    */   public MapView<Integer, Base.BasicView> getNotOwnedAndNotVisibleBases()
/* 332:    */   {
/* 333:462 */     new MapView.Transform(this.other_notvisible_bases, new Util.Converter()
/* 334:    */     {
/* 335:    */       public Base.BasicView convert(Base src)
/* 336:    */       {
/* 337:465 */         return src.restrictedView();
/* 338:    */       }
/* 339:    */     });
/* 340:    */   }
/* 341:    */   
/* 342:    */   public Country.View getCountry()
/* 343:    */   {
/* 344:475 */     return (Country.View)Util.view(this.ai_country);
/* 345:    */   }
/* 346:    */   
/* 347:    */   public boolean isTimeOut()
/* 348:    */   {
/* 349:484 */     return this.cm.isTimeOut();
/* 350:    */   }
/* 351:    */   
/* 352:    */   public void updateSimFrame()
/* 353:    */   {
/* 354:493 */     this.idm.updateData();
/* 355:    */   }
/* 356:    */   
/* 357:    */   public void sendCommand(Command c)
/* 358:    */   {
/* 359:503 */     this.cm.sendCommand(c);
/* 360:    */   }
/* 361:    */   
/* 362:    */   public void quit(int code)
/* 363:    */   {
/* 364:512 */     if (this.idm != null) {
/* 365:513 */       this.idm.terminate();
/* 366:    */     }
/* 367:514 */     if (this.client_ai != null) {
/* 368:515 */       this.client_ai.end();
/* 369:    */     }
/* 370:516 */     if (this.cm != null)
/* 371:    */     {
/* 372:518 */       this.cm.terminate();
/* 373:    */       try
/* 374:    */       {
/* 375:520 */         this.cm.join();
/* 376:    */       }
/* 377:    */       catch (InterruptedException e)
/* 378:    */       {
/* 379:522 */         e.printStackTrace();
/* 380:    */       }
/* 381:    */     }
/* 382:525 */     log.debug("Gracefully terminated the client");
/* 383:526 */     System.exit(code);
/* 384:    */   }
/* 385:    */   
/* 386:    */   static class StateConverter
/* 387:    */   {
/* 388:    */     public static Plane.State make(PlaneStateData sd)
/* 389:    */     {
/* 390:532 */       Plane.State s = null;
/* 391:533 */       switch (sd)
/* 392:    */       {
/* 393:    */       case IDLE: 
/* 394:536 */         s = Plane.State.AT_AIRPORT;
/* 395:537 */         break;
/* 396:    */       case FOLLOWING: 
/* 397:539 */         s = Plane.State.ATTACKING;
/* 398:540 */         break;
/* 399:    */       case ATTACKING: 
/* 400:542 */         s = Plane.State.IDLE;
/* 401:543 */         break;
/* 402:    */       case AT_AIRPORT: 
/* 403:545 */         s = Plane.State.GOING_TO;
/* 404:546 */         break;
/* 405:    */       case LANDING: 
/* 406:548 */         s = Plane.State.DEAD;
/* 407:549 */         break;
/* 408:    */       case DEAD: 
/* 409:551 */         s = Plane.State.FOLLOWING;
/* 410:552 */         break;
/* 411:    */       case GOING_TO: 
/* 412:554 */         s = Plane.State.LANDING;
/* 413:555 */         break;
/* 414:    */       default: 
/* 415:557 */         throw new Error("Unhandled plane state");
/* 416:    */       }
/* 417:559 */       return s;
/* 418:    */     }
/* 419:    */   }
/* 420:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     proxy.Proxy
 * JD-Core Version:    0.7.0.1
 */