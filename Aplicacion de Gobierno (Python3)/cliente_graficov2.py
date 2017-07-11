 ##################################################
 # Universidad de Pinar del Rio
 # Facultad de Ciencias Técnicas
 # Carrera de Telecomunicaciones y Electrónica
 ##################################################
 # Proyecto: Proyecto Final de 3er Año
 # Nombre  : Control Remoto de Estación de Bombeo
 # Autor   : José Guerra Carmenate
 ##################################################
 # Cliente TCP/IP para control de estacion de bombeo v2
 # for Python 3.1.1
 ##################################################
import tkinter
import tkinter as tk
import tkinter.scrolledtext as scrolledtext
import threading as thread 
import socket
import time
IP = '192.168.4.1'
PORT = 5656

class Estado:
	def __init__(self):
		self.bomba = "OFF";
		self.buzzer = "ON";
		self.tanque = "NO Lleno";

def get_attrib_value( label, attrib ): #dada una etiqueta y un atributo devuelve el valor de este atributo 
	"""Dada una etiqueta completa y un atributo esta funcion retorna el valor de este atributo.
		--> En caso de error de sintaxis lo reporta
		Ej1: get_attrib_value( '<pepe come="mucho"/>', 'come')
		retornaria 'mucho'
		Ej2: get_attrib_value( '<pepe come="mucho" comida="pan" >', 'comida')
		retornaria 'pan'
	"""
	i = label.find(attrib+"=");
	if i == -1: return "ERROR, no existe atributo ("+attrib+")\n";
	i += len(attrib)+1
	if label[i] != '"': return "ERROR, el valor de '"+attrib+"' no está en comillas" 
	ini = i+1
	end = label.find( '"', ini )
	if end == -1: return "ERROR, falta comilla de cierre"
	return label[ini:end];

def get_label_name( label ):
	""" Dada una etiqueta retorna el nombre o identificador de la etiqueta
		Ej1: get_label_name( '<rele tipo="chino" estado="ON" >' )
		retornaria 'rele'
	"""
	i = label.find('<')
	if i == -1: return "ERROR no existe marca de etiqueta(<)"
	return label[i+1:label.find(' ')]

def decode_state( xml_state ):
	"""Esta funcion toma todo el entramado xml generado y enviado por el sistema
		y lo decodifica en informacion legible para la interfaz de usuario
	"""
	result = ""
	result +=( "Nombre: " );
	xml_state = xml_state.split('\r\n');
	result += ( get_attrib_value(xml_state[0], 'name') ) + "\n"
	result += ( "Control: " + get_attrib_value(xml_state[0], 'control') )+'\n\n'
	
	for i in range(1, len(xml_state)-1):
		result += ( get_label_name(xml_state[i])+":\t" );
		if get_label_name(xml_state[i]) != "Tanque_Elevado":
			result += '\t';
		result += ( get_attrib_value(xml_state[i], 'estado')+'\n' );
	return result

class ActualizarEstado( ):
	""" Esta clase se encarga de recibir el entramado de estado y teniendo
		en cuenta el nuevo estado actualizar la Interfaz de Usuario.
	"""
	def __init__(  self, server, mainframe ):
		self.server = server
		self.winframe = mainframe
		self.cont = 0;
		while True:
			print('try')
			try:
				self.new_state_xml = self.server.recv(1024)
				self.cont += 1
			except:
				print('el servidor no envia nada!!!'.encode('ascii'))
				break;
			print( self.new_state_xml )
			self.dec = decode_state( self.new_state_xml.decode('ascii') )
			self.tmp = self.dec.split('\n');
			for line in self.tmp:
				if line.find('Bomba') != -1:
					if line.find("ON") != -1:
						self.winframe.switch_bomb['text'] = "Apagar\nBomba";
					else:
						self.winframe.switch_bomb['text'] = "Encender\nBomba";

				elif line.find('Buzzer') != -1:
					if line.find("ON") != -1:
						self.winframe.switch_buzzer['text'] = "Apagar\nBuzzer";
					else:
						self.winframe.switch_buzzer['text'] = "Encender\nBuzzer";

				elif line.find('Control') != -1:
					if line.find('Manual') != -1:
						self.winframe.switch_control['text'] = "Activar Control\nAutonomo"
					elif line.find('Autonomo') != -1:
						self.winframe.switch_control['text'] = "Activar Control\nManual"
			if self.winframe.debug_active == False:
				self.winframe.table_of_info['text'] = self.dec + '\n' + str(self.cont) 
			else:
				self.winframe.table_of_info['text'] = self.new_state_xml.decode('ascii') + '\n' + str(self.cont) 
			
			if self.winframe.switch_control['text'].find("Autonomo") != -1:
				self.winframe.switch_bomb['state'] = 'normal'
				self.winframe.switch_buzzer['state'] = 'normal'
			else:
				self.winframe.switch_bomb['state'] = 'disabled'
				self.winframe.switch_buzzer['state'] = 'disabled'


class MainWindow(tk.Frame):
	""" Esta clase crea el Frame de la Interfaz de Usuario"""
	def __init__( self ):
		tk.Frame.__init__( self )
		self['relief'] = 'groove'
		self['borderwidth'] = 5
		self.pack();
		#Vars
		self.debug_active = False

		#WindowConfig
		self.master.title( "Cliente TCP" )
		self.ConectionFrame_is_active = False;

		self.titulo = tk.Label( self, text="Control Remoto de Estación de Bombeo")
		self.titulo['font'] = self.titulo['font'].split()[0] + " 20" 
		self.titulo['relief'] = 'ridge'
		self.titulo['borderwidth'] = 5
		self.titulo.grid( sticky=tk.N, columnspan=3 )
		
		self.switch_bomb = tk.Button( self, text="Switch Bomb\nOn/Off")
		self.switch_bomb.grid(row = 2, column=0, sticky=tk.W )
		self.switch_bomb['width'] = '15';

		self.switch_buzzer = tk.Button( self, text="Switch Buzzer\nOn/Off" )
		self.switch_buzzer.grid( row = 3, column=0, sticky=tk.W )
		self.switch_buzzer['width'] = '15';

		self.switch_active_debug = tk.Button( self, text="Ver Entramado" )
		self.switch_active_debug['width'] = '15'
		self.switch_active_debug.grid( row=4, column=0, sticky=tk.W )
		
		self.switch_control = tk.Button( self, text="Activar Control\nAutonomo" )
		self.switch_control['width'] = '15'
		self.switch_control.grid( row = 5, column=0, sticky=tk.W );
				
		self.table_of_info = tk.Label( self )
		self.table_of_info['font'] = self.table_of_info['font'].split()[0] + ' 15'
		self.table_of_info['bg'] = 'white'
		self.table_of_info['borderwidth'] = 5
		self.table_of_info['height'] = 15
		self.table_of_info['state'] = 'normal'
		self.table_of_info['justify'] = 'left'
		self.table_of_info['width']  = 50
		self.table_of_info['relief'] = 'ridge'
		self.table_of_info['anchor'] = 'nw'
		self.table_of_info.grid( sticky=tk.W, row = 1, column=1, rowspan=5 );


class App( thread.Thread ):
	def __init__( self, master ):
		thread.Thread.__init__( self )
		self.client = socket.socket();
		print( "ip: " +IP + " port: " + str(PORT) )
		self.client.connect( (IP, PORT) )
		self.current_state = Estado();
		self.mainFrame = MainWindow()
		self.mainFrame.pack()
		self.mainFrame.switch_bomb['command']=self.sw_bomb_func
		self.mainFrame.switch_buzzer['command']=self.sw_buzzer_func
		self.mainFrame.switch_control['command']=self.sw_control_func
		self.mainFrame.switch_active_debug['command']=self.sw_debug_active_func

	def run( self ):
		ActualizarEstado( self.client, self.mainFrame )

	def send_data(self, sms):
		#self.client2 = socket.socket();
		#self.client2.connect( (IP,PORT) );
		self.client.send( bytes(sms.encode('ascii')) )
		#self.client2.close()
		
	def sw_bomb_func(self):
		if self.mainFrame.switch_bomb['text'].find( 'Encender' ) != -1:
			self.send_data( '<Bomba estado="ON"/>' )
		else:
			self.send_data( '<Bomba estado="OFF"/>' )
		print( 'sw_bomb' )
	def sw_buzzer_func(self):
		if self.mainFrame.switch_buzzer['text'].find( 'Encender' ) != -1:
			self.send_data( '<Buzzer estado="ON"/>' )
		else:
			self.send_data('<Buzzer estado="OFF"/>')
		print( 'sw_buzzer' )
	def sw_control_func(self): 
		if self.mainFrame.switch_control['text'].find( 'Autonomo' ) != -1:
			self.send_data( '<Control estado="Autonomo"/>' )
		else:
			self.send_data( '<Control estado="Manual"/>' )
		print( 'sw_control' )
	
	def sw_debug_active_func(self):
		if self.mainFrame.switch_active_debug['text'].find( 'Entramado' ) != -1:
			self.mainFrame.debug_active = True;
			self.mainFrame.switch_active_debug['text'] = 'Ver Informe'
		else:
			self.mainFrame.debug_active = False;
			self.mainFrame.switch_active_debug['text'] = 'Ver Entramado'

def main():
	root = tk.Tk()

	app = App( root )
	app.start()
	root.mainloop()
	app.client.close()
	

		
if __name__ == '__main__':
	main()

