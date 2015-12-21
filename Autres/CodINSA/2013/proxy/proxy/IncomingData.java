/*   1:    */ package proxy;
/*   2:    */ 
/*   3:    */ import genbridge.Bridge.Client;
/*   4:    */ import genbridge.ConnectionData;
/*   5:    */ import genbridge.Data;
/*   6:    */ import genbridge.InitData;
/*   7:    */ import org.apache.thrift.TException;
/*   8:    */ import org.apache.thrift.protocol.TBinaryProtocol;
/*   9:    */ import org.apache.thrift.protocol.TProtocol;
/*  10:    */ import org.apache.thrift.transport.TSocket;
/*  11:    */ import org.apache.thrift.transport.TTransport;
/*  12:    */ import org.slf4j.Logger;
/*  13:    */ 
/*  14:    */ public class IncomingData
/*  15:    */ {
/*  16:    */   private Proxy proxy;
/*  17:    */   private int connection_id;
/*  18:    */   private int player_id;
/*  19:    */   private Bridge.Client client;
/*  20:    */   
/*  21:    */   public IncomingData(String ip, int port, Proxy p)
/*  22:    */   {
/*  23: 25 */     this.proxy = p;
/*  24:    */     try
/*  25:    */     {
/*  26: 31 */       TTransport transport = new TSocket(ip, port);
/*  27: 32 */       transport.open();
/*  28:    */       
/*  29: 34 */       TProtocol protocol = new TBinaryProtocol(transport);
/*  30: 35 */       this.client = new Bridge.Client(protocol);
/*  31:    */     }
/*  32:    */     catch (Exception e)
/*  33:    */     {
/*  34: 38 */       Proxy.log.error("Error while connecting to the server. Message: " + e.getMessage() + "\nCause : The server is not running, the game may have begun, ended or, the port or the ip could be wrong");
/*  35: 39 */       this.proxy.quit(1);
/*  36:    */     }
/*  37:    */   }
/*  38:    */   
/*  39:    */   public int getIdConnection()
/*  40:    */   {
/*  41: 45 */     return this.connection_id;
/*  42:    */   }
/*  43:    */   
/*  44:    */   public int getPlayerId()
/*  45:    */   {
/*  46: 48 */     return this.player_id;
/*  47:    */   }
/*  48:    */   
/*  49:    */   public void retrieveInitialData()
/*  50:    */   {
/*  51:    */     try
/*  52:    */     {
/*  53: 55 */       ConnectionData cd = this.client.connect("Banane2");
/*  54: 56 */       this.player_id = cd.player_id;
/*  55: 57 */       this.connection_id = cd.con_id;
/*  56: 59 */       if (this.connection_id < 0)
/*  57:    */       {
/*  58: 61 */         Proxy.log.error("Error while connecting to the server.\nCause : Id returned by server is invalid.");
/*  59: 62 */         this.proxy.quit(2);
/*  60:    */       }
/*  61:    */       else
/*  62:    */       {
/*  63: 65 */         Proxy.log.debug("Connected with id: " + this.connection_id + ". You are player n°" + this.player_id);
/*  64:    */       }
/*  65: 67 */       Proxy.log.debug("Retrieving initial data");
/*  66: 68 */       InitData d = this.client.retrieveInitData(this.connection_id);
/*  67:    */       
/*  68: 70 */       this.proxy.setInitData(d);
/*  69:    */     }
/*  70:    */     catch (TException e)
/*  71:    */     {
/*  72: 73 */       Proxy.log.error("Unexpected error while retrieving initial data from server. Message: " + e.getMessage());
/*  73:    */       
/*  74: 75 */       this.proxy.quit(3);
/*  75:    */     }
/*  76:    */   }
/*  77:    */   
/*  78:    */   public void updateData()
/*  79:    */   {
/*  80:    */     try
/*  81:    */     {
/*  82: 82 */       Data d = this.client.retrieveData(this.connection_id);
/*  83: 83 */       if (d.numFrame < 0)
/*  84:    */       {
/*  85: 85 */         if (d.numFrame == -1)
/*  86:    */         {
/*  87: 87 */           Proxy.log.debug("Received an end-of-game frame id (-1), stopping.");
/*  88: 88 */           this.proxy.quit(0);
/*  89:    */         }
/*  90:    */         else
/*  91:    */         {
/*  92: 92 */           Proxy.log.warn("Error: frame sent by the server is not valid (number " + d.numFrame + "). Ignoring");
/*  93: 93 */           this.proxy.quit(4);
/*  94:    */         }
/*  95:    */       }
/*  96:    */       else {
/*  97: 97 */         this.proxy.updateProxyData(d);
/*  98:    */       }
/*  99:    */     }
/* 100:    */     catch (TException e)
/* 101:    */     {
/* 102:100 */       Proxy.log.error("Unexpected error while retrieving data from server. Message: " + e.getMessage());
/* 103:101 */       this.proxy.quit(3);
/* 104:    */     }
/* 105:    */   }
/* 106:    */   
/* 107:    */   public void terminate()
/* 108:    */   {
/* 109:107 */     if (this.client.getInputProtocol().getTransport().isOpen()) {
/* 110:108 */       this.client.getInputProtocol().getTransport().close();
/* 111:    */     }
/* 112:109 */     if (this.client.getOutputProtocol().getTransport().isOpen()) {
/* 113:110 */       this.client.getOutputProtocol().getTransport().close();
/* 114:    */     }
/* 115:    */   }
/* 116:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     proxy.IncomingData
 * JD-Core Version:    0.7.0.1
 */