/*   1:    */ package proxy;
/*   2:    */ 
/*   3:    */ import command.AttackCommand;
/*   4:    */ import command.BuildPlaneCommand;
/*   5:    */ import command.CancelRequestCommand;
/*   6:    */ import command.Command;
/*   7:    */ import command.DropMilitarsCommand;
/*   8:    */ import command.ExchangeResourcesCommand;
/*   9:    */ import command.FillFuelTankCommand;
/*  10:    */ import command.FollowCommand;
/*  11:    */ import command.LandCommand;
/*  12:    */ import command.MoveCommand;
/*  13:    */ import command.WaitCommand;
/*  14:    */ import common.Immutable;
/*  15:    */ import genbridge.AttackCommandData;
/*  16:    */ import genbridge.BuildPlaneCommandData;
/*  17:    */ import genbridge.CancelBuildRequestCommandData;
/*  18:    */ import genbridge.CommandData;
/*  19:    */ import genbridge.CommandReceiver.Client;
/*  20:    */ import genbridge.CoordData;
/*  21:    */ import genbridge.DropMilitarsCommandData;
/*  22:    */ import genbridge.ExchangeResourcesCommandData;
/*  23:    */ import genbridge.FillFuelTankCommandData;
/*  24:    */ import genbridge.FollowCommandData;
/*  25:    */ import genbridge.LandCommandData;
/*  26:    */ import genbridge.MoveCommandData;
/*  27:    */ import genbridge.PlaneCommandData;
/*  28:    */ import genbridge.Response;
/*  29:    */ import genbridge.WaitCommandData;
/*  30:    */ import java.util.LinkedList;
/*  31:    */ import java.util.Queue;
/*  32:    */ import model.AbstractBase.View;
/*  33:    */ import model.Coord.View;
/*  34:    */ import model.Country.Request.View;
/*  35:    */ import model.Plane.BasicView;
/*  36:    */ import model.Plane.FullView;
/*  37:    */ import model.Plane.Type;
/*  38:    */ import org.apache.thrift.TException;
/*  39:    */ import org.apache.thrift.protocol.TBinaryProtocol;
/*  40:    */ import org.apache.thrift.protocol.TProtocol;
/*  41:    */ import org.apache.thrift.transport.TSocket;
/*  42:    */ import org.apache.thrift.transport.TTransport;
/*  43:    */ import org.slf4j.Logger;
/*  44:    */ 
/*  45:    */ public class CommandSender
/*  46:    */   extends Thread
/*  47:    */ {
/*  48:    */   private CommandReceiver.Client client;
/*  49:    */   private boolean isTimeOut;
/*  50:    */   private int idConnection;
/*  51:    */   private Proxy proxy;
/*  52:    */   private boolean running;
/*  53:    */   private Queue<Command> waitingList;
/*  54:    */   
/*  55:    */   public CommandSender(String ip, int port, int idC, Proxy p)
/*  56:    */   {
/*  57: 53 */     this.proxy = p;
/*  58: 54 */     this.running = false;
/*  59: 55 */     this.waitingList = new LinkedList();
/*  60: 56 */     this.isTimeOut = false;
/*  61: 57 */     this.idConnection = idC;
/*  62:    */     try
/*  63:    */     {
/*  64: 63 */       TTransport transport = new TSocket(ip, port);
/*  65: 64 */       transport.open();
/*  66:    */       
/*  67: 66 */       TProtocol protocol = new TBinaryProtocol(transport);
/*  68:    */       
/*  69:    */ 
/*  70: 69 */       this.client = new CommandReceiver.Client(protocol);
/*  71:    */     }
/*  72:    */     catch (Exception e)
/*  73:    */     {
/*  74: 72 */       Proxy.log.error("Error while connecting to the server. Message: " + 
/*  75: 73 */         e.getMessage() + "\nCause : The server is not running, the game may have ended or, the port or the ip may be not good");
/*  76: 74 */       this.proxy.quit(1);
/*  77:    */     }
/*  78:    */   }
/*  79:    */   
/*  80:    */   public synchronized boolean isTimeOut()
/*  81:    */   {
/*  82: 79 */     return this.isTimeOut;
/*  83:    */   }
/*  84:    */   
/*  85:    */   public synchronized void newFrame()
/*  86:    */   {
/*  87: 83 */     this.isTimeOut = false;
/*  88:    */   }
/*  89:    */   
/*  90:    */   public void run()
/*  91:    */   {
/*  92: 88 */     this.running = true;
/*  93: 90 */     while (this.running) {
/*  94: 91 */       synchronized (this)
/*  95:    */       {
/*  96:    */         for (;;)
/*  97:    */         {
/*  98:    */           try
/*  99:    */           {
/* 100: 95 */             wait();
/* 101:    */           }
/* 102:    */           catch (InterruptedException ie)
/* 103:    */           {
/* 104: 98 */             ie.printStackTrace();
/* 105:    */           }
/* 106: 92 */           if (this.waitingList.isEmpty()) {
/* 107: 92 */             if (!this.running) {
/* 108:    */               break;
/* 109:    */             }
/* 110:    */           }
/* 111:    */         }
/* 112:    */         do
/* 113:    */         {
/* 114:102 */           Command currentCmd = (Command)this.waitingList.remove();
/* 115:103 */           sendThriftCommand(currentCmd);
/* 116:101 */           if (this.waitingList.isEmpty()) {
/* 117:    */             break;
/* 118:    */           }
/* 119:101 */         } while (this.running);
/* 120:    */       }
/* 121:    */     }
/* 122:108 */     if (this.client.getInputProtocol().getTransport().isOpen()) {
/* 123:109 */       this.client.getInputProtocol().getTransport().close();
/* 124:    */     }
/* 125:110 */     if (this.client.getOutputProtocol().getTransport().isOpen()) {
/* 126:111 */       this.client.getOutputProtocol().getTransport().close();
/* 127:    */     }
/* 128:    */   }
/* 129:    */   
/* 130:    */   public synchronized void sendCommand(Command cmd)
/* 131:    */   {
/* 132:115 */     this.waitingList.add(cmd);
/* 133:116 */     notify();
/* 134:    */   }
/* 135:    */   
/* 136:    */   private void sendThriftCommand(Command cmd)
/* 137:    */   {
/* 138:120 */     Proxy.log.debug("Sending command : " + cmd);
/* 139:121 */     Response r = null;
/* 140:    */     try
/* 141:    */     {
/* 142:    */       try
/* 143:    */       {
/* 144:124 */         cmd.match();
/* 145:    */       }
/* 146:    */       catch (MoveCommand c)
/* 147:    */       {
/* 148:127 */         r = this.client.sendMoveCommand(
/* 149:128 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 150:    */       }
/* 151:    */       catch (WaitCommand c)
/* 152:    */       {
/* 153:131 */         r = this.client.sendWaitCommand(
/* 154:132 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 155:    */       }
/* 156:    */       catch (LandCommand c)
/* 157:    */       {
/* 158:135 */         r = this.client.sendLandCommand(
/* 159:136 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 160:    */       }
/* 161:    */       catch (AttackCommand c)
/* 162:    */       {
/* 163:138 */         r = this.client.sendAttackCommand(
/* 164:139 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 165:    */       }
/* 166:    */       catch (FollowCommand c)
/* 167:    */       {
/* 168:141 */         r = this.client.sendFollowCommand(
/* 169:142 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 170:    */       }
/* 171:    */       catch (DropMilitarsCommand c)
/* 172:    */       {
/* 173:144 */         r = this.client.sendDropMilitarsCommand(
/* 174:145 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 175:    */       }
/* 176:    */       catch (FillFuelTankCommand c)
/* 177:    */       {
/* 178:147 */         r = this.client.sendFillFuelTankCommand(
/* 179:148 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 180:    */       }
/* 181:    */       catch (ExchangeResourcesCommand c)
/* 182:    */       {
/* 183:150 */         r = this.client.sendExchangeResourcesCommandData(
/* 184:151 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 185:    */       }
/* 186:    */       catch (BuildPlaneCommand c)
/* 187:    */       {
/* 188:153 */         r = this.client.sendBuildPlaneCommand(
/* 189:154 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 190:    */       }
/* 191:    */       catch (CancelRequestCommand c)
/* 192:    */       {
/* 193:156 */         r = this.client.sendCancelBuildRequestCommandData(
/* 194:157 */           DataMaker.make(c, this.proxy.getNumFrame()), this.idConnection);
/* 195:    */       }
/* 196:160 */       treatResult(r);
/* 197:    */     }
/* 198:    */     catch (TException e)
/* 199:    */     {
/* 200:163 */       Proxy.log.error("Unexpected error received while sending a command. Message: " + 
/* 201:164 */         e.getMessage());
/* 202:165 */       e.printStackTrace();
/* 203:166 */       this.proxy.quit(1);
/* 204:    */     }
/* 205:    */   }
/* 206:    */   
/* 207:    */   private void treatResult(Response r)
/* 208:    */   {
/* 209:172 */     switch (r.code)
/* 210:    */     {
/* 211:    */     case 0: 
/* 212:174 */       Proxy.log.debug("Command sent successfully !");
/* 213:175 */       break;
/* 214:    */     case -3: 
/* 215:177 */       this.isTimeOut = true;
/* 216:178 */       Proxy.log.warn("Command is time out !");
/* 217:179 */       break;
/* 218:    */     case -1: 
/* 219:181 */       Proxy.log.warn("The command has been accepted but : " + r.message);
/* 220:182 */       break;
/* 221:    */     case -2: 
/* 222:    */     default: 
/* 223:184 */       Proxy.log.warn("The command has been ignored ! code:" + r.code + ", message: " + 
/* 224:185 */         r.message);
/* 225:    */     }
/* 226:    */   }
/* 227:    */   
/* 228:    */   public void terminate()
/* 229:    */   {
/* 230:190 */     this.running = false;
/* 231:191 */     synchronized (this)
/* 232:    */     {
/* 233:193 */       notify();
/* 234:    */     }
/* 235:    */   }
/* 236:    */   
/* 237:    */   public static class DataMaker
/* 238:    */   {
/* 239:    */     static CoordData make(Coord.View c)
/* 240:    */     {
/* 241:200 */       return new CoordData(c.x(), c.y());
/* 242:    */     }
/* 243:    */     
/* 244:    */     public static BuildPlaneCommandData make(BuildPlaneCommand c, int numFrame)
/* 245:    */     {
/* 246:205 */       return new BuildPlaneCommandData(new CommandData(numFrame), c.requestedType.id);
/* 247:    */     }
/* 248:    */     
/* 249:    */     static LandCommandData make(LandCommand cmd, int numFrame)
/* 250:    */     {
/* 251:209 */       return new LandCommandData(new PlaneCommandData(new CommandData(
/* 252:210 */         numFrame), cmd.plane.id()), cmd.base.id());
/* 253:    */     }
/* 254:    */     
/* 255:    */     static AttackCommandData make(AttackCommand cmd, int numFrame)
/* 256:    */     {
/* 257:214 */       return new AttackCommandData(new PlaneCommandData(new CommandData(
/* 258:215 */         numFrame), cmd.planeSrc.id()), cmd.planeTarget.id());
/* 259:    */     }
/* 260:    */     
/* 261:    */     static FollowCommandData make(FollowCommand cmd, int numFrame)
/* 262:    */     {
/* 263:219 */       return new FollowCommandData(new PlaneCommandData(new CommandData(
/* 264:220 */         numFrame), cmd.planeSrc.id()), cmd.planeTarget.id());
/* 265:    */     }
/* 266:    */     
/* 267:    */     static MoveCommandData make(MoveCommand cmd, int numFrame)
/* 268:    */     {
/* 269:224 */       return new MoveCommandData(new PlaneCommandData(new CommandData(
/* 270:225 */         numFrame), cmd.plane.id()), make((Coord.View)cmd.destination.view));
/* 271:    */     }
/* 272:    */     
/* 273:    */     static WaitCommandData make(WaitCommand cmd, int numFrame)
/* 274:    */     {
/* 275:229 */       return new WaitCommandData(new PlaneCommandData(new CommandData(
/* 276:230 */         numFrame), cmd.plane.id()));
/* 277:    */     }
/* 278:    */     
/* 279:    */     static DropMilitarsCommandData make(DropMilitarsCommand cmd, int numFrame)
/* 280:    */     {
/* 281:234 */       return new DropMilitarsCommandData(new PlaneCommandData(new CommandData(
/* 282:235 */         numFrame), cmd.planeSrc.id()), cmd.baseTarget.id(), cmd.quantity);
/* 283:    */     }
/* 284:    */     
/* 285:    */     static FillFuelTankCommandData make(FillFuelTankCommand cmd, int numFrame)
/* 286:    */     {
/* 287:239 */       return new FillFuelTankCommandData(new PlaneCommandData(new CommandData(
/* 288:240 */         numFrame), cmd.planeSrc.id()), cmd.quantity);
/* 289:    */     }
/* 290:    */     
/* 291:    */     static ExchangeResourcesCommandData make(ExchangeResourcesCommand cmd, int numFrame)
/* 292:    */     {
/* 293:244 */       return new ExchangeResourcesCommandData(new PlaneCommandData(new CommandData(
/* 294:245 */         numFrame), cmd.planeSrc.id()), cmd.militarQuantity, cmd.fuelQuantity, cmd.deleteResources);
/* 295:    */     }
/* 296:    */     
/* 297:    */     static CancelBuildRequestCommandData make(CancelRequestCommand c, int numFrame)
/* 298:    */     {
/* 299:250 */       return new CancelBuildRequestCommandData(new CommandData(numFrame), c.request.rqId());
/* 300:    */     }
/* 301:    */   }
/* 302:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     proxy.CommandSender
 * JD-Core Version:    0.7.0.1
 */