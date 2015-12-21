/*   1:    */ package ai;
/*   2:    */ 
/*   3:    */ import command.AttackCommand;
/*   4:    */ import command.Command;
/*   5:    */ import command.LandCommand;
/*   6:    */ import command.MoveCommand;
/*   7:    */ import common.CollectionView;
/*   8:    */ import common.MapView;
/*   9:    */ import java.io.PrintStream;
/*  10:    */ import java.util.ArrayList;
/*  11:    */ import java.util.Iterator;
/*  12:    */ import java.util.List;
/*  13:    */ import java.util.Scanner;
/*  14:    */ import model.AbstractBase.View;
/*  15:    */ import model.Base.BasicView;
/*  16:    */ import model.Base.FullView;
/*  17:    */ import model.Coord.View;
/*  18:    */ import model.Country.View;
/*  19:    */ import model.Plane.BasicView;
/*  20:    */ import model.Plane.FullView;
/*  21:    */ import proxy.Proxy;
/*  22:    */ 
/*  23:    */ public class ConsoleAI
/*  24:    */   extends AbstractAI
/*  25:    */ {
/*  26:    */   public ConsoleAI(String ip, int port)
/*  27:    */   {
/*  28: 24 */     super(ip, port);
/*  29:    */   }
/*  30:    */   
/*  31:    */   public void think()
/*  32:    */   {
/*  33: 29 */     think_blocking();
/*  34:    */   }
/*  35:    */   
/*  36:    */   public void think_blocking()
/*  37:    */   {
/*  38: 33 */     Scanner in = new Scanner(System.in);
/*  39:    */     Object localObject;
/*  40:143 */     for (;; ((Iterator)localObject).hasNext())
/*  41:    */     {
/*  42: 38 */       System.out.print("Next action ([move|land|attk] id; list; exit): ");
/*  43:    */       
/*  44: 40 */       String[] cmd = in.nextLine().split(" ");
/*  45:    */       
/*  46: 42 */       System.out.print("Processing command... ");
/*  47: 43 */       System.out.flush();
/*  48:    */       
/*  49: 45 */       this.game.updateSimFrame();
/*  50:    */       
/*  51:    */ 
/*  52:    */ 
/*  53:    */ 
/*  54:    */ 
/*  55:    */ 
/*  56: 52 */       MapView<Integer, Base.BasicView> bases = this.game.getAllBases();
/*  57: 53 */       MapView<Integer, Plane.FullView> planes = this.game.getMyPlanes();
/*  58: 54 */       MapView<Integer, Plane.BasicView> ennemy_planes = this.game.getEnnemyPlanes();
/*  59:    */       
/*  60: 56 */       List<Command> coms = new ArrayList();
/*  61:    */       try
/*  62:    */       {
/*  63: 59 */         boolean recognized = true;
/*  64: 60 */         switch ((localObject = cmd[0]).hashCode())
/*  65:    */         {
/*  66:    */         case 3004906: 
/*  67: 60 */           if (((String)localObject).equals("attk")) {}
/*  68:    */           break;
/*  69:    */         case 3127582: 
/*  70: 60 */           if (((String)localObject).equals("exit")) {
/*  71:    */             break label914;
/*  72:    */           }
/*  73:    */           break;
/*  74:    */         case 3314155: 
/*  75: 60 */           if (((String)localObject).equals("land")) {
/*  76:    */             break;
/*  77:    */           }
/*  78:    */           break;
/*  79:    */         case 3322014: 
/*  80: 60 */           if (((String)localObject).equals("list")) {}
/*  81:    */         case 3357649: 
/*  82: 60 */           if ((goto 793) && (((String)localObject).equals("move")))
/*  83:    */           {
/*  84: 64 */             if (cmd.length != 2) {
/*  85:    */               break label804;
/*  86:    */             }
/*  87: 66 */             int id = Integer.parseInt(cmd[1]);
/*  88: 67 */             Base.BasicView b = (Base.BasicView)bases.get(Integer.valueOf(id));
/*  89: 68 */             Coord.View c = null;
/*  90: 70 */             if (b == null)
/*  91:    */             {
/*  92: 71 */               if (this.game.getCountry().id() != id)
/*  93:    */               {
/*  94: 73 */                 System.err.println("This id isn't corresponding neither to a base nor your country");
/*  95:    */                 break label804;
/*  96:    */               }
/*  97: 77 */               c = this.game.getCountry().position();
/*  98:    */             }
/*  99:    */             else
/* 100:    */             {
/* 101: 79 */               c = b.position();
/* 102:    */             }
/* 103: 81 */             for (Plane.FullView p : planes.valuesView()) {
/* 104: 82 */               coms.add(new MoveCommand(p, c));
/* 105:    */             }
/* 106:    */             break label804;
/* 107: 87 */             int id = Integer.parseInt(cmd[1]);
/* 108: 88 */             Base.BasicView b = (Base.BasicView)bases.get(Integer.valueOf(id));
/* 109: 89 */             AbstractBase.View c = null;
/* 110: 91 */             if (b == null)
/* 111:    */             {
/* 112: 92 */               if (this.game.getCountry().id() != id)
/* 113:    */               {
/* 114: 94 */                 System.err.println("You can't see this base, move around it before you land");
/* 115:    */                 break label804;
/* 116:    */               }
/* 117: 98 */               c = this.game.getCountry();
/* 118:    */             }
/* 119:    */             else
/* 120:    */             {
/* 121:100 */               c = b;
/* 122:    */             }
/* 123:102 */             for (Plane.FullView p : planes.valuesView()) {
/* 124:103 */               coms.add(new LandCommand(p, c));
/* 125:    */             }
/* 126:    */             break label804;
/* 127:108 */             Plane.BasicView ep = (Plane.BasicView)ennemy_planes.get(Integer.valueOf(Integer.parseInt(cmd[1])));
/* 128:109 */             if (ep == null)
/* 129:    */             {
/* 130:111 */               System.err.println("Bad id, this plane does not exists");
/* 131:    */             }
/* 132:    */             else
/* 133:    */             {
/* 134:114 */               for (Plane.FullView p : planes.valuesView()) {
/* 135:115 */                 coms.add(new AttackCommand(p, ep));
/* 136:    */               }
/* 137:    */               break label804;
/* 138:118 */               System.out.println();
/* 139:119 */               System.out.println(">> My planes:");
/* 140:120 */               for (Plane.FullView p : planes.valuesView()) {
/* 141:121 */                 System.out.println(p);
/* 142:    */               }
/* 143:122 */               System.out.println(">> Ennemy planes:");
/* 144:123 */               for (Plane.BasicView p : ennemy_planes.valuesView()) {
/* 145:124 */                 System.out.println(p);
/* 146:    */               }
/* 147:125 */               System.out.println(">> Visible bases :");
/* 148:126 */               for (Base.FullView b : this.game.getVisibleBase().valuesView()) {
/* 149:127 */                 System.out.println(b);
/* 150:    */               }
/* 151:128 */               System.out.println(">> Your Country");
/* 152:129 */               System.out.println(this.game.getCountry());
/* 153:    */             }
/* 154:    */           }
/* 155:130 */           break;
/* 156:    */         }
/* 157:132 */         recognized = false;
/* 158:133 */         System.err.println("Unrecognized command!");
/* 159:    */         label804:
/* 160:135 */         if (recognized) {
/* 161:136 */           System.out.println("Processed");
/* 162:    */         }
/* 163:    */       }
/* 164:    */       catch (IllegalArgumentException e)
/* 165:    */       {
/* 166:139 */         System.out.println("Command failed: " + e);
/* 167:140 */         System.err.println("Command failed: " + e);
/* 168:    */       }
/* 169:143 */       localObject = coms.iterator(); continue;Command c = (Command)((Iterator)localObject).next();
/* 170:144 */       this.game.sendCommand(c);
/* 171:    */     }
/* 172:    */     label914:
/* 173:148 */     in.close();
/* 174:149 */     this.game.quit(0);
/* 175:    */   }
/* 176:    */   
/* 177:    */   public void think_async()
/* 178:    */   {
/* 179:153 */     Scanner in = new Scanner(System.in);
/* 180:    */     
/* 181:    */ 
/* 182:    */ 
/* 183:    */ 
/* 184:    */ 
/* 185:    */ 
/* 186:    */ 
/* 187:    */ 
/* 188:    */ 
/* 189:    */ 
/* 190:    */ 
/* 191:    */ 
/* 192:    */ 
/* 193:    */ 
/* 194:    */ 
/* 195:    */ 
/* 196:170 */     Thread updater = new Thread()
/* 197:    */     {
/* 198:157 */       public volatile boolean active = true;
/* 199:    */       
/* 200:    */       public void run()
/* 201:    */       {
/* 202:161 */         while (this.active) {
/* 203:162 */           synchronized (this)
/* 204:    */           {
/* 205:163 */             ConsoleAI.this.game.updateSimFrame();
/* 206:    */           }
/* 207:    */         }
/* 208:    */       }
/* 209:170 */     };
/* 210:171 */     updater.start();
/* 211:    */     Plane.FullView p;
/* 212:232 */     for (;; p.hasNext())
/* 213:    */     {
/* 214:184 */       System.out.print("Next action ([move|land|attk] id; exit to quit): ");
/* 215:    */       
/* 216:    */ 
/* 217:187 */       String[] cmd = in.nextLine().split(" ");
/* 218:    */       
/* 219:    */ 
/* 220:    */ 
/* 221:    */ 
/* 222:    */ 
/* 223:    */ 
/* 224:    */ 
/* 225:    */ 
/* 226:    */ 
/* 227:197 */       MapView<Integer, Base.BasicView> bases = this.game.getAllBases();
/* 228:198 */       MapView<Integer, Plane.FullView> planes = this.game.getMyPlanes();
/* 229:199 */       MapView<Integer, Plane.BasicView> ennemy_planes = this.game.getEnnemyPlanes();
/* 230:    */       
/* 231:    */ 
/* 232:    */ 
/* 233:    */ 
/* 234:204 */       List<Command> coms = new ArrayList();
/* 235:    */       String str;
/* 236:206 */       switch ((str = cmd[0]).hashCode())
/* 237:    */       {
/* 238:    */       case 3004906: 
/* 239:206 */         if (str.equals("attk")) {}
/* 240:    */         break;
/* 241:    */       case 3127582: 
/* 242:206 */         if (str.equals("exit")) {
/* 243:    */           break label505;
/* 244:    */         }
/* 245:    */         break;
/* 246:    */       case 3314155: 
/* 247:206 */         if (str.equals("land")) {
/* 248:    */           break;
/* 249:    */         }
/* 250:    */       case 3357649: 
/* 251:206 */         if ((goto 451) && (str.equals("move")))
/* 252:    */         {
/* 253:210 */           Base.BasicView b = (Base.BasicView)bases.get(Integer.valueOf(Integer.parseInt(cmd[1])));
/* 254:211 */           for (Plane.FullView p : planes.valuesView()) {
/* 255:212 */             coms.add(new MoveCommand(p, b.position()));
/* 256:    */           }
/* 257:    */           break label459;
/* 258:216 */           Base.BasicView b = (Base.BasicView)bases.get(Integer.valueOf(Integer.parseInt(cmd[1])));
/* 259:217 */           if ((b instanceof Base.FullView))
/* 260:    */           {
/* 261:218 */             for (??? = planes.valuesView().iterator(); ???.hasNext();)
/* 262:    */             {
/* 263:218 */               p = (Plane.FullView)???.next();
/* 264:219 */               coms.add(new LandCommand(p, (Base.FullView)b));
/* 265:    */             }
/* 266:    */           }
/* 267:    */           else
/* 268:    */           {
/* 269:221 */             System.err.println("You can't see this base, move around it before you land");
/* 270:    */             break label459;
/* 271:225 */             for (Plane.FullView p : planes.valuesView()) {
/* 272:226 */               coms.add(new AttackCommand(p, (Plane.BasicView)ennemy_planes.get(Integer.valueOf(Integer.parseInt(cmd[1])))));
/* 273:    */             }
/* 274:    */           }
/* 275:    */         }
/* 276:227 */         break;
/* 277:    */       }
/* 278:229 */       System.err.println("Unrecognized command!");
/* 279:    */       label459:
/* 280:232 */       p = coms.iterator();
/* 281:232 */       continue;Command c = (Command)p.next();
/* 282:233 */       this.game.sendCommand(c);
/* 283:    */     }
/* 284:    */     label505:
/* 285:255 */     in.close();
/* 286:256 */     updater.active = false;
/* 287:    */     try
/* 288:    */     {
/* 289:258 */       updater.join();
/* 290:    */     }
/* 291:    */     catch (InterruptedException e)
/* 292:    */     {
/* 293:260 */       e.printStackTrace();
/* 294:    */     }
/* 295:    */   }
/* 296:    */   
/* 297:    */   public static void main(String[] args)
/* 298:    */     throws InterruptedException
/* 299:    */   {
/* 300:265 */     if (args.length != 2)
/* 301:    */     {
/* 302:267 */       System.out.println("Usage : java MoveAI ip port");
/* 303:268 */       System.exit(1);
/* 304:    */     }
/* 305:270 */     String ip = args[0];
/* 306:271 */     int port = Integer.parseInt(args[1]);
/* 307:    */     
/* 308:273 */     AbstractAI ai = new ConsoleAI(ip, port);
/* 309:274 */     ai.think();
/* 310:    */   }
/* 311:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     ai.ConsoleAI
 * JD-Core Version:    0.7.0.1
 */