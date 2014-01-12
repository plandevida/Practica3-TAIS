#pragma once

#include "JuegoLogT2.h"
#include "InterfazGrafT2.h"
#include "JugadorAutoT2.h"

#include "Juego3enRaya.h"
#include "InterfazGraf3enRaya.h"
#include "JugadorAlea3enRaya.h"

#include "JuegoOthello.h"
#include "InterfazGrafOthello.h"
#include "JugadorAleaOthello.h"
#include "JugadorMinimaxOthello.h"

//#include "JuegoConecta4.h"
//#include "InterfazGrafConecta4.h"
//#include "JugadorAleaConecta4.h"
//#include "JugadorMinimaxConecta4.h"

namespace JuegosReunidos {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	typedef enum {conecta4, tresEnRaya, otelo} enuJuego;
	typedef enum {otro, alea, minimax} enuJugador;
	typedef enum {bajo=2, medio=4, alto=6} enuNivel;
	typedef enum {humano, maquina} enuPartida;

	/// <summary>
	/// Resumen de Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

			iniciar();
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~Form1()
		{
			if (components) { delete components; }

			liberar();
		}
	protected: 

	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		System::ComponentModel::Container ^components;

		enuJuego juego;            // juego seleccionado
		enuJugador tipoJugador;    // tipo de jugador para la máquina
		enuNivel nivel;            // nivel del jugador (profundidad del árbol de juego)
		JuegoLogT2* partida;       // apunta a un objeto del juego concreto al que se está jugando
		InterfazGrafT2* interfaz;  //        a una interfaz para ese juego
		JugadorAutoT2* jugador;    //        a un jugador automático para ese juego
		Turno jugIni;              // jugador que comienza la partida
		int milSeg;

	private: System::Windows::Forms::PictureBox^  Tablero;
	private: System::Windows::Forms::MenuStrip^  Menu;
	private: System::Windows::Forms::ToolStripMenuItem^  juegoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tresEnRayaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  oteloToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  jugadorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aleatorioToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  inteligenteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  altoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  medioToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bajoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  partidaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  usuarioToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ordenadorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  conecta4ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  salirToolStripMenuItem;

			 void iniciar() {
				 milSeg = 1000;  // espera antes de que la maquina juegue

				 // juego inicial por defecto
				 juego = tresEnRaya;
				 tipoJugador = alea;
				 nivel = bajo;

				 /*partida = new Juego3enRaya();
				 interfaz = new InterfazGraf3enRaya(Tablero->Width, Tablero->Height);
				 jugador = new JugadorAlea3enRaya();*/
				 
				 partida = new JuegoOthello();
				 interfaz = new InterfazGrafOthello(Tablero->Width, Tablero->Height);
				 jugador = new JugadorAleaOthello();

				 jugIni = Jhum;
				 partida->reinicia(jugIni);
			 }

			 void liberar(){
				 delete partida;
				 delete jugador;
				 delete interfaz;
			 }

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Método necesario para admitir el Diseñador. No se puede modificar
			 /// el contenido del método con el editor de código.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->Tablero = (gcnew System::Windows::Forms::PictureBox());
				 this->Menu = (gcnew System::Windows::Forms::MenuStrip());
				 this->juegoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->tresEnRayaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->conecta4ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->oteloToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->jugadorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->aleatorioToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->inteligenteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->altoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->medioToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->bajoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->partidaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->usuarioToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ordenadorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->salirToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Tablero))->BeginInit();
				 this->Menu->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // Tablero
				 // 
				 this->Tablero->BackColor = System::Drawing::Color::Gainsboro;
				 this->Tablero->Location = System::Drawing::Point(0, 27);
				 this->Tablero->Name = L"Tablero";
				 this->Tablero->Size = System::Drawing::Size(435, 435);
				 this->Tablero->TabIndex = 0;
				 this->Tablero->TabStop = false;
				 this->Tablero->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Tablero_Paint);
				 this->Tablero->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Tablero_MouseUp);
				 // 
				 // Menu
				 // 
				 this->Menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->juegoToolStripMenuItem,
						 this->jugadorToolStripMenuItem, this->partidaToolStripMenuItem, this->salirToolStripMenuItem
				 });
				 this->Menu->Location = System::Drawing::Point(0, 0);
				 this->Menu->Name = L"Menu";
				 this->Menu->Size = System::Drawing::Size(434, 24);
				 this->Menu->TabIndex = 1;
				 this->Menu->Text = L"menuStrip1";
				 // 
				 // juegoToolStripMenuItem
				 // 
				 this->juegoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->tresEnRayaToolStripMenuItem,
						 this->conecta4ToolStripMenuItem, this->oteloToolStripMenuItem
				 });
				 this->juegoToolStripMenuItem->Name = L"juegoToolStripMenuItem";
				 this->juegoToolStripMenuItem->Size = System::Drawing::Size(50, 20);
				 this->juegoToolStripMenuItem->Text = L"Juego";
				 // 
				 // tresEnRayaToolStripMenuItem
				 // 
				 this->tresEnRayaToolStripMenuItem->Name = L"tresEnRayaToolStripMenuItem";
				 this->tresEnRayaToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				 this->tresEnRayaToolStripMenuItem->Text = L"Tres en raya";
				 this->tresEnRayaToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::tresEnRayaToolStripMenuItem_Click);
				 // 
				 // conecta4ToolStripMenuItem
				 // 
				 this->conecta4ToolStripMenuItem->Name = L"conecta4ToolStripMenuItem";
				 this->conecta4ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				 this->conecta4ToolStripMenuItem->Text = L"Conecta 4";
				 // 
				 // oteloToolStripMenuItem
				 // 
				 this->oteloToolStripMenuItem->Name = L"oteloToolStripMenuItem";
				 this->oteloToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				 this->oteloToolStripMenuItem->Text = L"Othello";
				 this->oteloToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::oteloToolStripMenuItem_Click);
				 // 
				 // jugadorToolStripMenuItem
				 // 
				 this->jugadorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->aleatorioToolStripMenuItem,
						 this->inteligenteToolStripMenuItem
				 });
				 this->jugadorToolStripMenuItem->Name = L"jugadorToolStripMenuItem";
				 this->jugadorToolStripMenuItem->Size = System::Drawing::Size(61, 20);
				 this->jugadorToolStripMenuItem->Text = L"Jugador";
				 // 
				 // aleatorioToolStripMenuItem
				 // 
				 this->aleatorioToolStripMenuItem->Name = L"aleatorioToolStripMenuItem";
				 this->aleatorioToolStripMenuItem->Size = System::Drawing::Size(130, 22);
				 this->aleatorioToolStripMenuItem->Text = L"Aleatorio";
				 this->aleatorioToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aleatorioToolStripMenuItem_Click);
				 // 
				 // inteligenteToolStripMenuItem
				 // 
				 this->inteligenteToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->altoToolStripMenuItem,
						 this->medioToolStripMenuItem, this->bajoToolStripMenuItem
				 });
				 this->inteligenteToolStripMenuItem->Name = L"inteligenteToolStripMenuItem";
				 this->inteligenteToolStripMenuItem->Size = System::Drawing::Size(130, 22);
				 this->inteligenteToolStripMenuItem->Text = L"Inteligente";
				 // 
				 // altoToolStripMenuItem
				 // 
				 this->altoToolStripMenuItem->Name = L"altoToolStripMenuItem";
				 this->altoToolStripMenuItem->Size = System::Drawing::Size(108, 22);
				 this->altoToolStripMenuItem->Text = L"Alto";
				 this->altoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::altoToolStripMenuItem_Click);
				 // 
				 // medioToolStripMenuItem
				 // 
				 this->medioToolStripMenuItem->Name = L"medioToolStripMenuItem";
				 this->medioToolStripMenuItem->Size = System::Drawing::Size(108, 22);
				 this->medioToolStripMenuItem->Text = L"Medio";
				 this->medioToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::medioToolStripMenuItem_Click);
				 // 
				 // bajoToolStripMenuItem
				 // 
				 this->bajoToolStripMenuItem->Name = L"bajoToolStripMenuItem";
				 this->bajoToolStripMenuItem->Size = System::Drawing::Size(108, 22);
				 this->bajoToolStripMenuItem->Text = L"Bajo";
				 this->bajoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bajoToolStripMenuItem_Click);
				 // 
				 // partidaToolStripMenuItem
				 // 
				 this->partidaToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->usuarioToolStripMenuItem,
						 this->ordenadorToolStripMenuItem
				 });
				 this->partidaToolStripMenuItem->Name = L"partidaToolStripMenuItem";
				 this->partidaToolStripMenuItem->Size = System::Drawing::Size(56, 20);
				 this->partidaToolStripMenuItem->Text = L"Partida";
				 // 
				 // usuarioToolStripMenuItem
				 // 
				 this->usuarioToolStripMenuItem->Name = L"usuarioToolStripMenuItem";
				 this->usuarioToolStripMenuItem->Size = System::Drawing::Size(131, 22);
				 this->usuarioToolStripMenuItem->Text = L"Usuario";
				 this->usuarioToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::usuarioToolStripMenuItem_Click);
				 // 
				 // ordenadorToolStripMenuItem
				 // 
				 this->ordenadorToolStripMenuItem->Name = L"ordenadorToolStripMenuItem";
				 this->ordenadorToolStripMenuItem->Size = System::Drawing::Size(131, 22);
				 this->ordenadorToolStripMenuItem->Text = L"Ordenador";
				 this->ordenadorToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::ordenadorToolStripMenuItem_Click);
				 // 
				 // salirToolStripMenuItem
				 // 
				 this->salirToolStripMenuItem->Name = L"salirToolStripMenuItem";
				 this->salirToolStripMenuItem->Size = System::Drawing::Size(41, 20);
				 this->salirToolStripMenuItem->Text = L"Salir";
				 this->salirToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::salirToolStripMenuItem_Click);
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::Color::Silver;
				 this->ClientSize = System::Drawing::Size(434, 461);
				 this->Controls->Add(this->Tablero);
				 this->Controls->Add(this->Menu);
				 this->MainMenuStrip = this->Menu;
				 this->MaximizeBox = false;
				 this->MaximumSize = System::Drawing::Size(450, 500);
				 this->MinimumSize = System::Drawing::Size(450, 500);
				 this->Name = L"Form1";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"Juegos Reunidos";
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Tablero))->EndInit();
				 this->Menu->ResumeLayout(false);
				 this->Menu->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void Tablero_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 interfaz->muestraEstado(e->Graphics,*partida);
			 }

	private: System::Void Tablero_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if ( e->Button == System::Windows::Forms::MouseButtons::Left ) {
					 int x = e->X; 
					 int y = Tablero->Height - e->Y;  // le damos la vuelta (en Windows el origen está arriba a la izquierda)
					 //string s = convertInt(e->Y); 
					 //String^ sm=gcnew String(s.c_str());
					 //MessageBox::Show(sm, "Pulsa Y", MessageBoxButtons::OKCancel, MessageBoxIcon::Asterisk);

					 if (!partida->final() && partida->dameTurno()==Jhum){
						 try{
							 // juega el humano
							 Casilla ca = interfaz->dameCasilla(x, y);
							 partida->aplicaJugada(ca);

							 Tablero->Refresh();  //para mostrar el estado

							 // juega el ordenador
							 if(!partida->final()){
								 Sleep(milSeg);
								 Casilla cb = jugador->juega(*partida);
								 partida->aplicaJugada(cb);
								 Tablero->Refresh();  //para mostrar el estado
							 }
						 }
						 catch(EInterfaz& e){MessageBox::Show(gcnew String(e.getMsg().c_str()), "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);}
						 catch(EJugador& e){MessageBox::Show(gcnew String(e.getMsg().c_str()), "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);}
						 catch(EJuego& e){MessageBox::Show(gcnew String(e.getMsg().c_str()), "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);}
					 }

				 }
			 }

	private: System::Void salirToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Close();
			 }

	private: System::Void usuarioToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 jugIni = Jhum;
				 partida->reinicia(Jhum);
				 Tablero->Refresh();
			 }
	private: System::Void ordenadorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 jugIni = Jmaq;
				 partida->reinicia(Jmaq);
				 Tablero->Refresh();
				 Sleep(milSeg);
				 jugador = new JugadorAleaOthello();
				 Casilla cb = jugador->juega(*partida);
				 partida->aplicaJugada(cb);
				 Tablero->Refresh();
			 }

	void cambiarNivelDificultad(enuNivel n) {
			tipoJugador = minimax;
			nivel = n;
			delete jugador;
			switch(juego){
			case otelo : 
				jugador = new JugadorMinimaxOthello(nivel); 
				break;
			case conecta4: //INCOMPLETO  jugador = new JugadorMinimaxConecta4(nivel); 
				break;
			}
			if(nivel==alto) altoToolStripMenuItem->Checked=true; else altoToolStripMenuItem->Checked=false;
			if(nivel==medio) medioToolStripMenuItem->Checked=true; else medioToolStripMenuItem->Checked=false;
			if(nivel==bajo) bajoToolStripMenuItem->Checked=true; else bajoToolStripMenuItem->Checked=false;

		}

private: System::Void altoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			cambiarNivelDificultad(alto);
		 }
private: System::Void medioToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			cambiarNivelDificultad(medio);
		 }
private: System::Void bajoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			cambiarNivelDificultad(bajo);
		 }


private: System::Void aleatorioToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 tipoJugador = alea;
			 delete jugador;
			 switch (juego) {
			 case conecta4:
				 //INCOMPLETO jugador = new JugadorAleaConecta4();
				 break;
			 case tresEnRaya:
				 jugador = new JugadorAlea3enRaya();
				 break;
			 case otelo:
				 jugador = new JugadorAleaOthello();
				 break;

			 }
		 }

private: System::Void tresEnRayaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(juego!=tresEnRaya) {
				 juego = tresEnRaya;
				 delete partida;
				 partida = new Juego3enRaya();
				 delete interfaz;
				 interfaz = new InterfazGraf3enRaya(Tablero->Width, Tablero->Height);
				 if (tipoJugador==alea) jugador = new JugadorAlea3enRaya();
				// else // tipoJugador == minimax
				//	 jugador = new JugadorMinimax3enRaya(nivel);
				 partida->reinicia(jugIni);
				 Tablero->Refresh();
			 }
		 }

private: System::Void oteloToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (juego != otelo) {
				 juego = otelo;
				 delete partida;
				 partida = new JuegoOthello();
				 delete interfaz;
				 interfaz = new InterfazGrafOthello(Tablero->Width, Tablero->Height);
				 if (tipoJugador == alea) jugador = new JugadorAleaOthello();
				 else // tipoJugador == minimax
					jugador = new JugadorMinimaxOthello(nivel);
				 partida->reinicia(jugIni);
				 Tablero->Refresh();
			 }
}

};
}
