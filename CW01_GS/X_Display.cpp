
void display_logo(int duration)
{
  ssd1306_clearScreen( );
  ssd1306_drawXBitmap(0, 0, 128, 64, x_logo);
  delay(duration);
}

void display_title_screen(int duration)
{
  OD01.clear();
  OD01.set2X();
  OD01.print("XK07 V");
  OD01.println(VERSION_REV);
  OD01.println("  GROUND   ");
  OD01.println("  STATION");
  delay(duration);
}

void display_connect_wifi()
{
  OD01.clear(0,128,0,5);
  OD01.set1X();
  OD01.println("");
  OD01.println("");

  OD01.println("Connect to ");
  String AP_name = "   XINABOX_12433567";          //NEEDS TO BE CHANGED
  OD01.println(AP_name);
  OD01.println("");
  OD01.println("Password:");
  OD01.println("      \"password\"");

  delay(2000);
  OD01.set2X();
  OD01.clear(0,128,0,1);
  OD01.setCursor(0,0);
  OD01.print("    0:30");
  delay(1000);

  for(int i = 29; i>-1; i--)
  {
  OD01.clear(72,128,0,1);

    if(i<10)
    {
      OD01.print("0"); OD01.print(i);
    }
    else
    {
      OD01.print(i);
    }

  delay(1000);
  }
}

void display_starting_screen(int duration)
{
  OD01.set2X();
  OD01.clear();
  OD01.println(" Starting");
  OD01.println("  Normal");
  OD01.print(" Operation");
  delay(duration);
}

void dislay_connecting_FS()
{
  OD01.set1X();
  OD01.clear();
  OD01.println("Unit Name: ");
  OD01.println("   Xinabox Demo");
  OD01.println();
  OD01.println("   Connecting to");
  OD01.println("   Flight Station");
  OD01.println();
  OD01.set2X();

  for(int i=0; i<4; i++)                    //NEEDS TO BE CHANGED
  {
    OD01.println("   .   ");
    delay(500);
    OD01.clear(0,128,6,8);
    OD01.println("   .   .   ");
    delay(500);
    OD01.clear(0,128,6,8);
    OD01.println("   .   .   .   ");
    delay(500);
    OD01.clear(0,128,6,8);
    OD01.println("   .   .   .   .");
    delay(500);
    OD01.clear(0,128,6,8);
  }
}

void display_connected_screen()
{
  OD01.set1X();
  OD01.clear(0,128,2,8);
  OD01.set2X() ;
  OD01.println(" Connected");
  delay(2000);
  OD01.set1X();
  OD01.println();
  OD01.println("  LOCAL RSSI:  -68dB");               //NEEDS TO BE CHANGED
  OD01.println("  SAT RSSI:    -59dB");
}