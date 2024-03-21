// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_L02GameMode.h"
#include "Galaga_USFX_L02Pawn.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaCaza.h"
#include "NaveEnemigaTransporte.h"

AGalaga_USFX_L02GameMode::AGalaga_USFX_L02GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AGalaga_USFX_L02Pawn::StaticClass();
	//NaveEnemiga01 = nullptr;
}

void AGalaga_USFX_L02GameMode::BeginPlay()
{
	Super::BeginPlay();
	//Set the game state to playing

	FVector ubicacionInicialNavesEnemigas = FVector(0.0f, 0.0f, 150.0f);
	FVector ubicacionActualNaveEnemiga = ubicacionInicialNavesEnemigas;
	FRotator rotacionNave = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		// Spawnear 10 instancias de ANaveEnemiga
		FVector StartLocation(0.f, 0.f, 0.f); // Posición inicial
		for (int i = 0; i < 10; ++i) {
			FVector SpawnLocation = StartLocation + FVector(i * 200.f, 100.f, 150.f); // Ajustar posición según el índice
			ANaveEnemiga* NuevaNaveEnemiga = GetWorld()->SpawnActor<ANaveEnemiga>(SpawnLocation, FRotator::ZeroRotator);
			if (NuevaNaveEnemiga) {
				TANavesEnemigas.Add(NuevaNaveEnemiga);
			}
		}

		// Spawnear 10 instancias de ANaveEnemigaCaza
		StartLocation = FVector(0.f, -100.f, 0.f); // Nueva posición inicial
		for (int i = 0; i < 10; ++i) {
			FVector SpawnLocation = StartLocation + FVector(i * 200.f, 100.f, 350.f); // Ajustar posición según el índice
			ANaveEnemigaCaza* NuevaNaveEnemigaCaza = GetWorld()->SpawnActor<ANaveEnemigaCaza>(SpawnLocation, FRotator::ZeroRotator);
			if (NuevaNaveEnemigaCaza) {
				TANavesEnemigasCaza.Add(NuevaNaveEnemigaCaza);
			}
		}

		// Spawnear 10 instancias de ANaveEnemigaTransporte
		StartLocation = FVector(0.f, 400.f, 0.f); // Nueva posición inicial
		for (int i = 0; i < 10; ++i) {
			FVector SpawnLocation = StartLocation + FVector(i * 200.f, 0.f, 0.f); // Ajustar posición según el índice
			ANaveEnemigaTransporte* NuevaNaveEnemigaTransporte = GetWorld()->SpawnActor<ANaveEnemigaTransporte>(SpawnLocation, FRotator::ZeroRotator);
			if (NuevaNaveEnemigaTransporte) {
				TANavesEnemigasTransporte.Add(NuevaNaveEnemigaTransporte);
			}
		}
		//for (int i = 0; i < 10; i++) {
		//	ANaveEnemigaCaza* NaveEnemigaCazaActual = World->SpawnActor<ANaveEnemigaCaza>(ubicacionActualNaveEnemiga, rotacionNave);
		//	//TANavesEnemigasCaza.Add(NaveEnemigaCazaActual);
		//	NaveEnemigaCazaActual->SetNombre("nave enemiga caza " + FString::FromInt(i));
		//	TANavesEnemigas.Add(NaveEnemigaCazaActual);
		//	TMPosicionesNavesEnemigas.Add(NaveEnemigaCazaActual, ubicacionActualNaveEnemiga);

		//	ubicacionActualNaveEnemiga.Y = ubicacionActualNaveEnemiga.Y + 150.0f;
		//}

		//ubicacionActualNaveEnemiga.X = ubicacionActualNaveEnemiga.X - 150.0f;
		//ubicacionActualNaveEnemiga.Y = ubicacionInicialNavesEnemigas.Y;
		//for (int j = 0; j < 10; j++) {
		//	
		//	ANaveEnemigaTransporte* NaveEnemigaTransporteActual = World->SpawnActor<ANaveEnemigaTransporte>(ubicacionActualNaveEnemiga, rotacionNave);
		//	//TANavesEnemigasTransporte.Add(NaveEnemigaTransporteActual);
		//	NaveEnemigaTransporteActual->SetNombre("nave enemiga transporte" + FString::FromInt(j));
		//	TANavesEnemigas.Add(NaveEnemigaTransporteActual);
		//	TMPosicionesNavesEnemigas.Add(NaveEnemigaTransporteActual, ubicacionActualNaveEnemiga);

		//	ubicacionActualNaveEnemiga.Y = ubicacionActualNaveEnemiga.Y + 150.0f;
		//}

		//FTimerHandle FTHVisualizacionPosicionesNavesEnemigas;

		//GetWorldTimerManager().SetTimer(FTHVisualizacionPosicionesNavesEnemigas, this, &AGalaga_USFX_L02GameMode::MostrarPosicionesNavesEnemigas, 1.0f, true);
		//
	}

}

void AGalaga_USFX_L02GameMode::MostrarPosicionesNavesEnemigas()
{
	for (auto ElementoActual : TMPosicionesNavesEnemigas) {
		ANaveEnemiga* naveEnemigaActual = ElementoActual.Key;
		FVector posicionActualNaveEnemiga = ElementoActual.Value;
		FString mensaje = "La nave " + naveEnemigaActual->GetNombre() + " esta en la posicion> " + posicionActualNaveEnemiga.ToString();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, mensaje);

			/*FString mensaje = "Nombre NaveEnemiga: " + Clave->GetNombre() + " Posicion NaveEnemiga: " + Valor.ToString();
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mensaje);*/

		}

		TMPosicionesNavesEnemigas[naveEnemigaActual] = naveEnemigaActual->GetActorLocation();
	}
}

